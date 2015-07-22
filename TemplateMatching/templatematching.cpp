#include "templatematching.h"

DLLExport void templateMatching(unsigned char* const data, int width, int height, int templatenumber, double thresh, int& x, int& y)
{
	// 探索画像
    cv::Mat src_search(height, width, CV_8UC4, data);
    //cv::Mat src_search(height, width, CV_16UC1, data);
	cv::Mat infraredImage;
	cv::cvtColor(src_search, infraredImage, CV_RGBA2GRAY);
	//cv::cvtColor(src_search, infraredImage, CV_RGBA2BGRA);

		 
	// テンプレート画像
	std::string tmp_img_filename = "./Template/tmp_" + std::to_string(templatenumber) + ".png"; 
	cv::Mat tmp_img = cv::imread(tmp_img_filename, 0);
		 
	// テンプレートマッチング
	cv::Mat result_img;
	//cv::Mat search_img;
	//infraredImage.convertTo(search_img, CV_8UC1, 255.0f / 65535, 0.0f);
	cv::matchTemplate(infraredImage, tmp_img, result_img, CV_TM_CCOEFF_NORMED);
	//cv::matchTemplate(search_img, tmp_img, result_img, CV_TM_CCOEFF_NORMED);

	// 最大のスコアの場所を探す
	cv::Rect roi_rect(0, 0, tmp_img.cols, tmp_img.rows);
	cv::Point max_pt;
	double maxVal;
	cv::minMaxLoc(result_img, NULL, &maxVal, NULL, &max_pt);
	roi_rect.x = max_pt.x;
	roi_rect.y = max_pt.y;
	std::cout << "(" << max_pt.x << ", " << max_pt.y << "), score=" << maxVal << std::endl;

	cv::Mat draw_image = infraredImage.clone();
		  
	// 探索結果の場所に矩形を描画
	if(maxVal > thresh){
		cv::cvtColor(draw_image, draw_image, CV_GRAY2BGR);
		cv::rectangle(draw_image, roi_rect, cv::Scalar(0,0,255), 3);

		x = max_pt.x + tmp_img.cols/2;
		y = max_pt.y + tmp_img.rows/2;
	}else{
		//閾値以下ならエラー値-1を入れておく
		x = -1;
		y = -1;
	}

	cv::imshow("search image", draw_image);
	cv::imshow("result image", result_img);

}

DLLExport void openWindow(const char* windowName)
{
    cv::namedWindow(windowName, CV_WINDOW_NORMAL);
}

DLLExport void closeWindow(const char* windowName)
{
	cv::destroyWindow(windowName);
}

