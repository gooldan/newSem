#include <algorithm>
#include <iostream> 
#include <math.h> 
#include <vector>
#include <complex>
#include "wav-file.h"
#include "wav-writer.h"
using namespace std;
const double pi = 3.14159265358979323846;
const double eps = 0.000001;

void ft(int n, int start, short *mas, vector<complex<double> > &res)
{
	double phi = -2 * pi / n;
	for (int i = 0; i < n; ++i)
	for (int j = 0; j < n; ++j)
		res[i] += complex<double>(mas[j + start], 0) * complex<double>(cos(phi*i*j), sin(phi*i*j));
}
void rft(int n, int start, short *mas, vector<complex<double> > &res)
{
	for (int i = 0; i < n; i++)
	{
		complex<double> s = 0;
		for (int j = 0; j < n; j++) 
		{
			s += res[j] * complex<double>(cos(2 * pi * i * j / n), sin(2 * pi * i * j / n));
		}
		mas[start + i] = s.real() / n;
	}
}
int main() {
	/**********************************************************************\
		ПРИМЕР №1
		Чтение данных из звукового wav-файла,
		вырезается часть файла с 30 по 50 секунду,
		вырезанная часть исходного файла записывается в новый wav-файл.
		\**********************************************************************/

	char* fileName = "example3_noisy.wav";
	// чтение файла.
	WavFile* pObjWavFile;
	std::cout << "FileName is: " << fileName;
	pObjWavFile = new WavFile;
	if (EXIT_SUCCESS != pObjWavFile->openWavFile(fileName))
	{
		std::cout << "\nCan't load wav file.";
		exit(-1);
	}

	// время начала и конца вырезаемого фрагмента (в секундах).
	double start_sec = 0;
	double end_sec = 5;

	// вывод на экран информации о файле.
	pObjWavFile->displayInformation(fileName);

	// частота дискретизации (в герцах).
	double sample_rate = pObjWavFile->getSampleRateHz();
	// количество каналов.
	int num_channels = pObjWavFile->getNumChannels();
	// количество отсчетов.
	int num_samples = pObjWavFile->getNumSamples();
	// если в файле несколько каналов, то они будут объединяться в один, поэтому
	num_samples /= num_channels;
	// массив отсчетов.
	short *data = new short[num_samples];
	short *datares = new short[num_samples];
	int count;
	// чтение данных.
	for (count = 0; pObjWavFile->ifMoreDataAvailable(); ++count)
	{
		data[count] = 0;
		// если в файле несколько каналов, объединяем их.
		for (int i = 0; i < num_channels; ++i) {
			data[count] += (short)pObjWavFile->readCurrentInput();
		}
		data[count] /= num_channels;
	}
	double size = count / sample_rate;

	int loudest;
	complex<double> loudestAmp;
	int part;
	double step = 0.012;
	for (double i = 0; i < size - step; i += step)
	{
		vector<complex<double>> res;
		res.resize(step*sample_rate + 1);
		ft(step*sample_rate + 1, sample_rate*i, data, res);
		int max = 0;
		for (int j = 0; j < res.size(); ++j)
		{
			//cout << abs(res[j]) << " " << abs(res[max])<<endl;
			if (abs(res[j])>abs(res[max]))
				max = j;
		}
		if (abs(res[max]) > abs(loudestAmp))
		{
			loudest = max;
			loudestAmp = res[max];
		}
		for (int j = 0; j < step*sample_rate; ++j)
		{
			//cout << abs(res[j]) << " " << abs(res[max]) << endl;
			if (abs(res[j]) < abs(res[max])*0.3)
				res[j] = 0;
		}

		rft(step*sample_rate + 1, sample_rate*i, datares, res);
	}
	// в новый файл записываем только отсчеты, соответсвующие вырезаемому фрагменту.
	cout << loudest / step << " hz";
	writeWAVData<short>("example3.wav", datares, (double)size*sample_rate * sizeof(short), (int)sample_rate, 1);
	delete[] data;
	delete pObjWavFile;
	delete[] datares;
	/**********************************************************************\
		ПРИМЕР №2
		Запись звукового сигнала по известным нотам. Каждая нота задается
		частотой и длительностью.
		\**********************************************************************/
	// количество нот.


	/*******************************************************************************\
		ЗАДАНИЕ
		Считайте звуковой сигнал из файла example3_noisy.wav.
		Сделайте преобразование Фурье для временных отсчетов исходого файла.
		Используйте окно размером в 12 миллисекунд.
		В полученном частотном пространстве
		а) определите значение частоты,
		на которой попугай кричит(говорит/поет) громче всего
		б) определите шумовые компоненты сигнала, понизьте или просто занулите
		амплитуды соответсвующих частот.
		Сделайте обратное преобразование Фурье.
		Запишите полученные временные отсчеты в файл example3.wav.
		В полученном файле шума должно стать меньше.
		\*******************************************************************************/

	return 0;
}
