#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
#if defined(__linux__)
    String face_cascade_name = "/usr/share/opencv/haarcascades/haarcascade_frontalface_alt.xml";
    String eyes_cascade_name = "/usr/share/opencv/haarcascades/haarcascade_eye_tree_eyeglasses.xml";
    String mouth_cascade_name = "/usr/share/opencv/haarcascades/haarcascade_mcs_mouth.xml";
    String nose_cascade_name = "/usr/share/opencv/haarcascades/haarcascade_mcs_nose.xml";
#elif defined(__APPLE__)
    String face_cascade_name = "/usr/local/Cellar/opencv/2.4.12/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml";
    String eyes_cascade_name = "/usr/local/Cellar/opencv/2.4.12/share/OpenCV/haarcascades/haarcascade_eye_tree_eyeglasses.xml";
    String mouth_cascade_name = "/usr/local/Cellar/opencv/2.4.12/share/OpenCV/haarcascades/haarcascade_mcs_mouth.xml";
    String nose_cascade_name = "/usr/local/Cellar/opencv/2.4.12/share/OpenCV/haarcascades/haarcascade_mcs_nose.xml";
#else
    String face_cascade_name = "C:\\haarcascades\\haarcascade_frontalface_alt.xml";
    String eyes_cascade_name = "C:\\haarcascades\\haarcascade_eye_tree_eyeglasses.xml";
    String mouth_cascade_name = "C:\\haarcascades\\haarcascade_mcs_mouth.xml";
    String nose_cascade_name = "C:\\haarcascades\\haarcascade_mcs_nose.xml";
#endif

    CascadeClassifier face_cascade;
    CascadeClassifier eyes_cascade;
    CascadeClassifier mouth_cascade;
    CascadeClassifier nose_cascade;

    face_cascade.load(face_cascade_name);
    eyes_cascade.load(eyes_cascade_name);
    mouth_cascade.load(mouth_cascade_name);
    nose_cascade.load(nose_cascade_name);

#if defined(__linux__) || defined(__APPLE__)
    Mat frame = imread("minhaz.jpg");
#else
    Mat frame = imread("C:\\minhaz.jpg");
#endif
    
    Mat frame_gray;
    vector<Rect> faces;

    cvtColor(frame, frame_gray, CV_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, CV_HAAR_SCALE_IMAGE, Size(30, 30));

    for(size_t f = 0; f < faces.size(); f++)
    {
        rectangle(frame, faces[f], Scalar(255,0,255), 2, CV_AA);

        Mat faceROI = frame_gray(faces[f]);

        // START DETECT EYES
        vector<Rect> eyes;
        eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 2, CV_HAAR_SCALE_IMAGE, Size(30, 30));

        for(size_t e = 0; e < eyes.size(); e++)
        {
            Rect eye;
            eye.x = faces[f].x + eyes[e].x;
            eye.y = faces[f].y + eyes[e].y;
            eye.width = eyes[e].width;
            eye.height = eyes[e].height;
            rectangle(frame, eye, Scalar(0,255,255), 2, CV_AA);
        }
        // END DETECT EYES


        // START DETECT MOUTH
        vector<Rect> mouths;
        mouth_cascade.detectMultiScale(faceROI, mouths, 1.1, 1, CV_HAAR_SCALE_IMAGE|CV_HAAR_FIND_BIGGEST_OBJECT, Size(30, 30));

        for(size_t m = 0; m < mouths.size(); m++)
        {
            Rect mouth;
            mouth.x = faces[f].x + mouths[m].x;
            mouth.y = faces[f].y + mouths[m].y;
            mouth.width = mouths[m].width;
            mouth.height = mouths[m].height;
            rectangle(frame, mouth, Scalar(255,255,0), 2, CV_AA);
        }
        // END DETECT MOUTH

        // START DETECT NOSE
        vector<Rect> noses;
        nose_cascade.detectMultiScale(faceROI, noses, 1.1, 2, CV_HAAR_SCALE_IMAGE|CV_HAAR_FIND_BIGGEST_OBJECT, Size(30, 30));

        for(size_t n = 0; n < noses.size(); n++)
        {
            Rect nose;
            nose.x = faces[f].x + noses[n].x;
            nose.y = faces[f].y + noses[n].y;
            nose.width = noses[n].width;
            nose.height = noses[n].height;
            rectangle(frame, nose, Scalar(0,255,0), 2, CV_AA);
        }
        // END DETECT NOSE
    }

    imshow("Face", frame);
    waitKey(0);
    return 0;
}
