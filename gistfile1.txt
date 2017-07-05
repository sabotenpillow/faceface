#include <opencv/cv.h>
#include <opencv/highgui.h>

void detectObj(const char *cascade_name, IplImage *img, IplImage *gImg, CvMemStorage *storage, int maxcount)
{
        CvHaarClassifierCascade *cascade = 0;
        CvSeq *seq;
        int i;
        static CvScalar colors[] = {
                {{0, 0, 255}}, {{0, 128, 255}},
                {{0, 255, 255}}, {{0, 255, 0}},
                {{255, 128, 0}}, {{255, 255, 0}},
                {{255, 0, 0}}, {{255, 0, 255}}
        };

        cascade = (CvHaarClassifierCascade *)cvLoad(cascade_name, 0, 0, 0);
        printf("find objects..."); fflush(stdout);
        seq = cvHaarDetectObjects(gImg, cascade, storage, 2.0, 4, 0, cvSize(40,40));
        printf("...done");
        for (i = 0; i < (seq ? seq->total : 0) && i < maxcount; i++) {
                CvRect *r = (CvRect *) cvGetSeqElem (seq, i);
                CvPoint center;
                int radius;
                center.x = cvRound (r->x + r->width * 0.5);
                center.y = cvRound (r->y + r->height * 0.5);
                radius = cvRound ((r->width + r->height) * 0.25);
                cvCircle (img, center, radius, colors[i % 8], 3, 8, 0);
        }
}

int main(int argc, char** argv)
{
        CvHaarClassifierCascade *cascade = 0;
        CvSeq *seq;
        IplImage *src_img = 0, *src_gray = 0;
        CvMemStorage *storage = 0;
        CvRect* face_rect;
        CvRect upper_half;
        CvRect lower_half;

        //Cascades
        const char *face_cascade = "/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt2.xml";
        const char *eye_cascade = "/usr/local/share/OpenCV/haarcascades/haarcascade_eye.xml";
        const char *nose_cascade = "/usr/local/share/OpenCV/haarcascades/haarcascade_mcs_nose.xml";
        const char *mouth_cascade = "/usr/local/share/OpenCV/haarcascades/haarcascade_mcs_mouth.xml";
        
        //Read ImageFile
        if (argc < 2 || (src_img = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR)) == 0)
                return -1;
        src_gray = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 1);
        //GrayScaleImage
        storage = cvCreateMemStorage(0);
        cvClearMemStorage(storage);
        cvCvtColor(src_img, src_gray, CV_BGR2GRAY);
        cvEqualizeHist(src_gray, src_gray);
        //Detect Face
        printf("Detecting face.."); fflush(stdout);
        int i;
        static CvScalar colors[] = {
                {{0, 0, 255}}, {{0, 128, 255}},
                {{0, 255, 255}}, {{0, 255, 0}},
                {{255, 128, 0}}, {{255, 255, 0}},
                {{255, 0, 0}}, {{255, 0, 255}}
        };

        cascade = (CvHaarClassifierCascade *)cvLoad(face_cascade, 0, 0, 0);
        printf("find objects..."); fflush(stdout);
        seq = cvHaarDetectObjects(src_gray, cascade, storage, 2.0, 4, 0, cvSize(40,40));
        printf("...done");
        if (seq->total > 0) {
                //顔領域を取得
                face_rect = (CvRect *) cvGetSeqElem(seq, 1);
                //顔の下半分の領域
                lower_half = cvRect(face_rect->x, face_rect->y + face_rect->height / 2,
                                face_rect->width, face_rect->height / 2);
                CvPoint center;
                int radius;
                center.x = cvRound (face_rect->x + face_rect->width * 0.5);
                center.y = cvRound (face_rect->y + face_rect->height * 0.5);
                radius = cvRound ((face_rect->width + face_rect->height) * 0.25);
                cvCircle (src_img, center, radius, colors[i % 8], 3, 8, 0);
                cvSetImageROI(src_img, *face_rect);
                cvSetImageROI(src_gray, *face_rect);
        } else {
                printf("no face detected\n");
                exit(-1);
        }
        printf("..done\n");
        //Detect Eyes
        printf("Detecting eyes.."); fflush(stdout);
        detectObj(eye_cascade, src_img, src_gray, storage, 2);
        printf("..done\n");
        //Detect Nose
        printf("Detecting nose.."); fflush(stdout);
        detectObj(nose_cascade, src_img, src_gray, storage, 1);
        printf("..done\n");
        //Detect Mouth

        cvResetImageROI(src_img);
        cvResetImageROI(src_gray);
        cvSetImageROI(src_img, lower_half);
        cvSetImageROI(src_gray, lower_half);
        printf("Detecting mouth.."); fflush(stdout);
        detectObj(mouth_cascade, src_img, src_gray, storage, 1);
        printf("..done\n");
        
        cvResetImageROI(src_img);
        cvResetImageROI(src_gray);
        
        //Show Image
        cvNamedWindow("Face detection", CV_WINDOW_AUTOSIZE);
        cvShowImage("Face Detection", src_img);
        cvWaitKey(0);
        //Cleanup
        cvReleaseImage(&src_img);
        cvReleaseImage(&src_gray);
        cvReleaseMemStorage(&storage);
        return 0;
}