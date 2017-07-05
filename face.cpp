#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

bool imageWrite(std::string filename, cv::Mat image);

int
main(int argc, char *argv[])
{
  const std::string filename   = "face.jpg";
  const std::string input_dir  = "images/";
  const std::string output_dir = "outlines/";
  const std::string base = input_dir + filename;
  const std::string dest = output_dir + filename;
  // const int contour_index = argc > 1 ? atoi(argv[1]) : 1;
  // const int max_level     = argc > 2 ? atoi(argv[2]) : 0;
  const int contour_index =  1;
  const int max_level     = 0;

  // read an image
  cv::Mat src_img = cv::imread(base, 1);
  if(src_img.empty()) return -1;

  // 2値化
  cv::Mat gray_img, bin_img;
  cv::cvtColor(src_img, gray_img, CV_BGR2GRAY);
  cv::threshold(gray_img, bin_img, 0, 255, cv::THRESH_BINARY|cv::THRESH_OTSU);

  /// 輪郭の検出
  std::vector<std::vector<cv::Point> > contours;
  std::vector<cv::Vec4i> hierarchy;
  // 2値画像，輪郭（出力），階層構造（出力），輪郭抽出モード，輪郭の近似手法
  cv::findContours(bin_img, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

  std::cout << "contour index = " << contour_index << std::endl;
  std::cout << "max level = " << max_level << std::endl;
  std::cout << "num of contours = " << contours.size() << std::endl;

  /// 輪郭の描画
  // 画像，輪郭，描画輪郭指定インデックス，色，太さ，種類，階層構造，描画輪郭の最大レベル
  cv::drawContours(src_img, contours, contour_index, cv::Scalar(0, 0, 200), 3, CV_AA, hierarchy, max_level);

  // write an image
  imageWrite(dest, src_img);
}


bool imageWrite(std::string path, cv::Mat image) {
  if(cv::imwrite(path, image))
    std::cout << "imwrite:" << path << " ... success" << std::endl;
  else
    std::cout << "imwrite:" << path << " ... failure" << std::endl;
}
