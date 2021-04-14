#include <opencv2\opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

int main() {
	double scale = 1.0;

	CascadeClassifier FaceDetection;
	FaceDetection.load("C:\\Users\\SHREESH\\Downloads\\opencv\\build\\etc\\haarcascades\\haarcascade_frontalface_alt.xml");

	//Function for using webcam
	VideoCapture cap(0);
	//If not capture return -1
	if (!cap.isOpened()) 
		return -1;

	for (;;) {
		//Create a matrix named frame, which will store our image
		Mat frame;
		cap >> frame;

		//OpenCv takes image on grayscale, so create a matrix named grayscale which will store converted original image
		Mat grayscale;
		//cvtColor will take frame as original location and grayscale where new image will be stored
		//COLOR_BGR2GRAY will convert frame image into gray
		cvtColor(frame, grayscale, COLOR_BGR2GRAY);
		//Resize the grayscale as originally there will be too much pixels to handle for face detection, lesser the pixel more the face detection is efficient
		resize(grayscale, grayscale, Size(grayscale.size().width / scale, grayscale.size().height / scale));

		//create vector rectangle which will be used in our frame to show detected faces
		vector<Rect> faces;
		FaceDetection.detectMultiScale(grayscale, faces, 1.1, 3, 0, Size(30, 30));

		for (Rect area : faces) {
			//drawcolor will set the color for rectangle which is used in frame for face detection
			//In this case 255 means blue
			Scalar drawcolor = Scalar(255, 0, 0);
			rectangle(frame, Point(cvRound(area.x * scale), cvRound(area.y * scale)),
				Point(cvRound((area.x + area.width - 1) * scale), cvRound((area.y + area.height - 1) * scale)), drawcolor);
		}

		imshow("WebCam", frame);

		if (waitKey(30) >= 0)
			break;

	}

	return 0;
}


