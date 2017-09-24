/*
	In order to protect the privacy, I've already deleted my personal photos

	If you want to run this program , please refer to my personal website : https://wonggwan.github.io/2017/09/20/FaceRecog-Detect/ for further detail
*/





//#include <iostream>
//#include <opencv2\opencv.hpp>
//#include <Windows.h>
//#include <stdio.h>
//using namespace cv;
//using namespace std;
//
//static CvMemStorage* storage = NULL;
//static CvHaarClassifierCascade* cascade = NULL;
//const char* cascadePath = "haarcascade_frontalface_alt_tree.xml";
//
//int main()
//{
//	int addcnt = 0;
//	char ImgName[32];
//
//	CvCapture* capture = cvCreateCameraCapture(0);
//	cvNamedWindow("Camera");
//
//	IplImage* cameraImage = NULL;
//	storage = cvCreateMemStorage(0);
//	cascade = (CvHaarClassifierCascade*)cvLoad(cascadePath);
//
//	while ((cameraImage = cvQueryFrame(capture)) != NULL)
//	{
//		cvWaitKey(1);
//		IplImage* grayImage = cvCreateImage(cvSize(cameraImage->width, cameraImage->height), 8, 1);
//		cvCvtColor(cameraImage, grayImage, CV_BGR2GRAY);
//
//		cvClearMemStorage(storage);
//		CvSeq* objects = cvHaarDetectObjects(grayImage, cascade, storage, 1.1, 2, 0, cvSize(30, 30));
//
//		IplImage* img_out;
//		Mat myFace;
//
//		for (int i = 0; i < (objects ? objects->total : 0); i++)
//		{
//			CvRect* rect = (CvRect*)cvGetSeqElem(objects, i);
//			cvRectangle(cameraImage, cvPoint(rect->x, rect->y),
//			cvPoint(rect->x + rect->width, rect->y + rect->height), cvScalar(0.0, 255));
//			CvSize size = cvSize(rect->width, rect->height);
//			cvSetImageROI(cameraImage, cvRect(rect->x, rect->y, rect->width, rect->height));
//			img_out = cvCreateImage(size, cameraImage->depth, cameraImage->nChannels);
//			cvCopy(cameraImage, img_out);
//			Mat a;
//			a = cv::Mat(img_out);
//			resize(a, myFace, Size(92, 112));
//			Mat last;
//			cvtColor(myFace, last, COLOR_BGR2GRAY);
//			sprintf(ImgName, "%d.jpg", addcnt);
//			imwrite(ImgName, last);
//			addcnt++;
//			cvResetImageROI(img_out);
//			cvResetImageROI(cameraImage);
//		}
//		cvShowImage("Camera", cameraImage);
//	}
//	return 0;
//}





//#include <opencv2/opencv.hpp>
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <math.h>
//#include <Windows.h>
//
//using namespace cv;
//using namespace std;
//
//static Mat norm_0_255(InputArray _src) {
//	Mat src = _src.getMat();
//	Mat dst;
//	switch (src.channels()) {
//	case1:
//		cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC1);
//		break;
//	case3:
//		cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC3);
//		break;
//	default:
//		src.copyTo(dst);
//		break;
//	}
//	return dst;
//}
//
//
//static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';') {
//	std::ifstream file(filename.c_str(), ifstream::in);
//	if (!file) {
//		string error_message = "No valid input file was given, please check the given filename.";
//		CV_Error(CV_StsBadArg, error_message);
//	}
//	string line, path, classlabel;
//	while (getline(file, line)) {
//		stringstream liness(line);
//		getline(liness, path, separator);
//		getline(liness, classlabel);
//		if (!path.empty() && !classlabel.empty()) {
//			images.push_back(imread(path, 0));
//			labels.push_back(atoi(classlabel.c_str()));
//		}
//	}
//}
//
//
//int main()
//{
//	string fn_csv = "at.txt";
//
//	vector<Mat> images;
//	vector<int> labels;
//
//	try
//	{
//		read_csv(fn_csv, images, labels);
//	}
//	catch (cv::Exception& e)
//	{
//		cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
//		exit(1);
//	}
//	if (images.size() <= 1) {
//		string error_message = "This demo needs at least 2 images to work. Please add more images to your data set!";
//		CV_Error(CV_StsError, error_message);
//	}
//	Mat testSample = images[images.size() - 1];
//	int testLabel = labels[labels.size() - 1];
//	images.pop_back();
//	labels.pop_back();
//
//	Ptr<FaceRecognizer> model = createEigenFaceRecognizer();
//	model->train(images, labels);
//	model->save("MyFacePCAModel.xml");
//
//	int predictedLabel = model->predict(testSample);
//	cout << predictedLabel << endl;
//	system("pause");
//	waitKey(0);
//	return 0;
//}










#include<opencv2\opencv.hpp>
#include<iostream>
#include<Windows.h>
#include<stdio.h>

using namespace std;
using namespace cv;

int main()
{
	int count = 0;
	int namecnt = 0;
	int not_in_database = 0;
	char ImgName[32];
	char NoName[32];

	VideoCapture cap(0);
	if (!cap.isOpened())
	{
		return -1;
	}
	Mat frame;
	Mat edges;
	Mat gray;

	CascadeClassifier cascade;
	bool stop = false;
	cascade.load("haarcascade_frontalface_alt.xml");

	Ptr<FaceRecognizer> modelPCA = createEigenFaceRecognizer();
	modelPCA->load("MyFacePCAModel.xml");

	while (!stop)
	{
		cap >> frame;
		vector<Rect> faces(2000);

		cvtColor(frame, gray, CV_BGR2GRAY);
		equalizeHist(gray, gray);

		cascade.detectMultiScale(gray, faces,
			1.1, 4, 0
			| CV_HAAR_SCALE_IMAGE,
			Size(30, 30));

		Mat face;
		Point text_lb;

		for (size_t i = 0; i < faces.size(); i++)
		{
			if (faces[i].height > 0 && faces[i].width > 0)
			{
				face = gray(faces[i]);
				text_lb = Point(faces[i].x, faces[i].y);

				rectangle(frame, faces[i], Scalar(255, 0, 0), 1, 8, 0);
			}
		}

		Mat face_test;
		int predictPCA = 0;
		if (face.rows >= 120)
		{
			resize(face, face_test, Size(92, 112));
		}

		if (!face_test.empty())
		{
			predictPCA = modelPCA->predict(face_test);
		}

		cout << predictPCA << endl;
		if (predictPCA == 35)
		{
			string name = "yourname";
			putText(frame, name, text_lb, FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255));
			cout << "Succeeded!" << endl << "yourname" << endl;
			count++;
		}
		if (predictPCA == 0)
		{
			if (faces.size() == 0)
			{
				count = 0;
				cout << "Failed" << endl;
			}
			else
			{
				count = 0;
				cout << "Not in the database" << endl;
				sprintf(NoName, "not_in_database%d.jpg", not_in_database);
				//imwrite(NoName, frame);
				not_in_database++;
			}
		}
		if (count == 1)
		{
			sprintf(ImgName, "yourname%d.jpg", namecnt);
			//imwrite(ImgName, frame);
			namecnt++;
		}
		imshow("face", frame);
		if (waitKey(10) >= 0)
		{
			waitKey(-1);
		}
	}
	not_in_database = 0;
	return 0;
}




