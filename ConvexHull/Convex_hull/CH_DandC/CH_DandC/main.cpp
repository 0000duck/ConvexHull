#include <iostream>
#include <cmath>
//#include <cstdlib>
#include <ctime>
#include <vector>
#include <stdlib.h>

#define MAX_NUM  3000

using namespace std;

struct  Point{
    int x;
    int y;
};

vector<Point> pts;//����ĵ㼯
vector<Point> ch;//͹���еĵ�

int getArea(Point p1, Point p2, Point p3) {
    return p1.x * p2.y + p3.x * p1.y + p2.x * p3.y -
             p3.x * p2.y - p2.x * p1.y - p1.x * p3.y;
}

/*���������������ǽ��������е�����Ԫ�ص�λ��*/
void swap(vector<Point> pts,int i,int j)
{
    Point tmp=pts[i];
    pts[i]=pts[j];
    pts[j]=tmp;
}

/*ѡ������*/
void SelectionSort(vector<Point> pts,int n)
{
    for(int i=0;i<n-1;i++)
    {
        int smallest=i;
        for(int j=i+1;j<n;j++)
        {
            if(pts[smallest].x>pts[j].x)
                smallest=j;
        }
        swap(pts,i,smallest);
    }
}

void d(Point p1, Point p2, vector<Point> s){
    if (s.empty()) {
       ch.push_back(p1);
       //ch.push_back(p2);
       return;
     }
    int area = 0;
    int maxArea = 0;
    Point pMax;
    for (int i = 0; i < s.size(); i++) {
        area = getArea(p1, p2, s[i]);//��������Ӧ�ĵ����Pmax
        if (area > maxArea) {
            pMax = s[i];
            maxArea = area;
        }
    }
    //�ҳ�λ��(p1, pMax)ֱ����ߵĵ㼯s1
    //�ҳ�λ��(pMax, p2)ֱ����ߵĵ㼯s2
    vector<Point> s1;
    vector<Point> s2;
    Point p3;
    for (int i = 0; i < s.size(); i++) {
        p3 = s[i];
        if (getArea(p1, pMax, p3) > 0) {
            s1.push_back(p3);
        } else if (getArea(pMax, p2, p3) > 0) {
            s2.push_back(p3);
        }
    }
       //�ݹ�
    d(p1, pMax, s1);
    d(pMax, p2, s2);
}

vector<Point> eval(){
    ch.clear();
    if(pts.empty())
        return ch;
    vector<Point> ptsLeft;//��͹���еĵ�
    vector<Point> ptsRight;//��͹���еĵ�
    //����
    SelectionSort(pts, pts.size());

    Point p1 = pts.front();//����ߵĵ�
    Point p2 = pts.back();//���ұߵĵ�,��ֱ��p1p2��ԭ͹���ֳ�����С͹��
    Point p3;
    int area = 0;
    for (int i = 1; i < pts.size(); i++) {//������еĵ�,
        p3 = pts[i];
        area = getArea(p1, p2, p3);
        if (area > 0) {
            ptsLeft.push_back(p3);//p3������
        } else if (area < 0) {
            ptsRight.push_back(p3);//p3������
        }
    }
    d(p1, p2, ptsLeft);//�ֱ����
    d(p2, p1, ptsRight);
    return ch;
}

int main()
{
    srand((unsigned)time(0));
    time_t c_start,c_end;
    for(int i=0;i<MAX_NUM;i++)
    {
        Point ptIn = { rand() % 101, rand() % 101 };
        pts.push_back(ptIn);
        cout << "("<<pts[i].x << ", " << pts[i].y <<")"<< endl;
    }
    cout<<endl;
    c_start=clock();
    eval();
    c_end=clock();
    for(int i=0;i<ch.size();i++)
    {
        cout<<"("<<ch[i].x<<","<<ch[i].y<<")"<<endl;
    }
    cout<<endl;
    cout<<"The running time is "<<difftime(c_end, c_start)/1000<<"s."<<endl;
    system("pause");
    return 0;
}

