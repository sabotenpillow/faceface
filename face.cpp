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

  /// 画像を表示するウィンドウ
  // ウィンドウの名前，プロパティ
  // CV_WINDOW_AUTOSIZE : ウィンドウサイズを画像サイズに合わせる
  // CV_WINDOW_FREERATIO : ウィンドウのアスペクト比を固定しない
  // cv::namedWindow("image1", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
  // ウィンドウ名でウィンドウを指定して，そこに画像を描画
  // cv::imshow("image1", src_img);
   
  // デフォルトのプロパティで表示
  // cv::imshow("image2", src_img);

  // キー入力を（無限に）待つ
  // cv::waitKey(0);

  // if(cv::imwrite("outlines/hoge.png", img1))
  //   std::cout << "imwrite:" << img1 << " ... success" << std::endl;
  // else
  //   std::cout << "imwrite:" << img1 << " ... failure" << std::endl;
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
