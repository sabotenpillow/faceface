#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

bool imageWrite(std::string filename, cv::Mat image);

int
main(int argc, char *argv[])
{
  const std::string filename   = "face.png";
  const std::string input_dir  = "images/";
  const std::string output_dir = "outlines/";
  const std::string base = input_dir + filename;
  const std::string dest = output_dir + filename;
  cv::Mat src_img = cv::imread(base, 1);
  if(src_img.empty()) return -1;

  // 3チャンネル，カラー画像として読み込む．
  cv::Mat img1 = cv::imread(base, 1);
  // グレースケール画像として読み込む．
  cv::Mat img2 = cv::imread(base, 0);
  // 画像をそのまま読み込む．ただし，アルファチャンネルは無視される．
  cv::Mat img3 = cv::imread(base, -1);

  imageWrite("outlines/hoge.png", img1);
  // imageWrite("outlines/piyo.png", img2);
  imageWrite(dest, img2);
  imageWrite("outlines/poyo.png", img3);
}


bool imageWrite(std::string path, cv::Mat image) {
  if(cv::imwrite(path, image))
    std::cout << "imwrite:" << path << " ... success" << std::endl;
  else
    std::cout << "imwrite:" << path << " ... failure" << std::endl;
}
