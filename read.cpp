#include <iostream>
#include <opencv2/highgui/highgui.hpp>

int
main(int argc, char *argv[])
{
  const std::string base = "images/face";
  std::vector<std::string> files;
  files.push_back(base + ".bmp"); // Windows bitmaps (bmp, dib)
  files.push_back(base + ".jpg"); // JPEG files (jpg, jpeg, jpe)
  files.push_back(base + ".jp2"); // JPEG 2000 files (jp2)
  files.push_back(base + ".png"); // Portable Network Graphics (png)
  files.push_back(base + ".pbm"); // Portable image format (pbm:raw)
  files.push_back(base + "_ascii" + ".pbm"); // Portable image format (pbm:ascii)
  files.push_back(base + ".pgm"); // Portable image format (pgm:raw)
  files.push_back(base + "_ascii" + ".pgm"); // Portable image format (pgm:ascii)
  files.push_back(base + ".ppm"); // Portable image format (ppm:raw)
  files.push_back(base + "_ascii" + ".ppm"); // Portable image format (ppm:ascii)
  files.push_back(base + ".ras"); // Sun rasters (ras, sr)
  files.push_back(base + ".tiff"); // TIFF files (tiff, tif)

  // cv::namedWindow("image1", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
  // cv::namedWindow("image2", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
  // cv::namedWindow("image3", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);

  std::vector<std::string>::iterator it = files.begin();
  for(;it!=files.end(); ++it) {
    std::cout << *it << std::endl;
    // 3チャンネル，カラー画像として読み込む．
    cv::Mat img1 = cv::imread(*it, 1);
    // グレースケール画像として読み込む．
    cv::Mat img2 = cv::imread(*it, 0);
    // 画像をそのまま読み込む．ただし，アルファチャンネルは無視される．
    cv::Mat img3 = cv::imread(*it, -1);

    // cv::imshow("image1", img1);
    // cv::imshow("image2", img2);
    // cv::imshow("image3", img3);

    if(cv::waitKey(0)==27) break;
  }
}
