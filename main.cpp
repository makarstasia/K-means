#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>


using namespace std;



// работа с координатами
struct Point {
    double x, y;     // координаты
    int cluster;     // изначальный кластер, по умолчанию это -1, т.к. точка не принадлежит ни к какому кластеру
    double minDist;  // минимальное расстояние до кластера - по умолчанию максимальное значение из С++

    Point() :
            x(0.0),
            y(0.0),
            cluster(-1),
            minDist(__DBL_MAX__) {}

    Point(double x, double y) :
            x(x),
            y(y),
            cluster(-1),
            minDist(__DBL_MAX__) {}

    double distance(Point p)
    {
        return (p.x - x) * (p.x - x) + (p.y - y) * (p.y - y); // вычисление евклидова расстояния
    }
};


//чтение csv файла
vector<Point> readcsv() {
    vector<Point> points;
    string line;
    ifstream file("/Users/amakarshina/CLionProjects/k-means/mall_data.csv");

    while (getline(file, line)) {
        stringstream lineStream(line);
        string bit;
        double x, y;
        getline(lineStream, bit, ',');
        x = stof(bit);
        getline(lineStream, bit, '\n');
        y = stof(bit);

        points.push_back(Point(x, y));
    }
    return points;
}


//непосредственно метод k-средних
void kMeansClustering(vector<Point>* points, int k)
//k-это количество кластеров
{

    //инициализация центроидов
    vector<Point> centroids;
    //srand(time(NULL));  // рандомное семя
    for (int i = 0; i < k; ++i) {
        centroids.push_back(points->at(rand()%100));
    }

    //назначение точек кластеру
    for (vector<Point>::iterator c = begin(centroids);
         c != end(centroids); ++c)
    {
        // быстрый способ получить индекс кластера
        //даем каждой точке кластера атрибут, который может содержать целочисленный индикатор
        //Затем мы устанавливаем этот идентификатор в индекс кластера, который находится ближе всего к точке.
        int clusterId = c - begin(centroids);

        for (vector<Point>::iterator it = points->begin();
             it != points->end(); ++it) {

            Point p = *it;
            double dist = c->distance(p);
            if (dist < p.minDist) {
                p.minDist = dist;
                p.cluster = clusterId;
            }
            *it = p;
        }
    }

    //Вычисление новых центроид
    vector<int> nPoints; //кол-во точек
    vector<double> sumX, sumY; //их суммы

// инициализация
    for (int j = 0; j < k; ++j) {
        nPoints.push_back(0);
        sumX.push_back(0.0);
        sumY.push_back(0.0);
    }

    // обновление данных
    for (vector<Point>::iterator it = points->begin();
         it != points->end(); ++it) {
        int clusterId = it->cluster;
        nPoints[clusterId] += 1;
        sumX[clusterId] += it->x;
        sumY[clusterId] += it->y;

        it->minDist = __DBL_MAX__;  // сбросим расстояние
    }

    // Вычислим новые центроиды
    for (vector<Point>::iterator c = begin(centroids);
         c != end(centroids); ++c) {
        int clusterId = c - begin(centroids);
        c->x = sumX[clusterId] / nPoints[clusterId];
        c->y = sumY[clusterId] / nPoints[clusterId];
    }


    //запись в файл
    ofstream myfile;
    myfile.open("/Users/amakarshina/CLionProjects/k-means/output.csv");
    myfile << "x,y,c" << endl;

    for (vector<Point>::iterator it = points->begin();
         it != points->end(); ++it) {
        myfile << it->x << "," << it->y << "," << it->cluster << endl;
    }
    myfile.close();

}


int main() {
    //запись в файл mall_data
    ofstream fout;
    fout.open("/Users/amakarshina/CLionProjects/k-means/mall_data.csv");
    for(int i = 0; i < 1000; i++)
    {
        fout <<to_string((double)rand() / RAND_MAX)+ "," + to_string((double)rand() / RAND_MAX)<< endl;
    }


    vector<Point> points = readcsv();
    kMeansClustering(&points, 5);
}
