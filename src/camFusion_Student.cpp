#include <iostream>
#include <algorithm>
#include <numeric>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "camFusion.hpp"
#include "dataStructures.h"

using namespace std;

// Create groups of Lidar points whose projection into the camera falls into the same bounding box
void clusterLidarWithROI(std::vector<BoundingBox> &boundingBoxes, std::vector<LidarPoint> &lidarPoints,
		float shrinkFactor, cv::Mat &P_rect_xx, cv::Mat &R_rect_xx, cv::Mat &RT)
{
	// loop over all Lidar points and associate them to a 2D bounding box
	cv::Mat X(4, 1, cv::DataType<double>::type);
	cv::Mat Y(3, 1, cv::DataType<double>::type);

	for (auto it1 = lidarPoints.begin(); it1 != lidarPoints.end(); ++it1)
	{
		// assemble vector for matrix-vector-multiplication
		X.at<double>(0, 0) = it1->x;
		X.at<double>(1, 0) = it1->y;
		X.at<double>(2, 0) = it1->z;
		X.at<double>(3, 0) = 1;

		// project Lidar point into camera
		Y = P_rect_xx * R_rect_xx * RT * X;
		cv::Point pt;
		pt.x = Y.at<double>(0, 0) / Y.at<double>(0, 2); // pixel coordinates
		pt.y = Y.at<double>(1, 0) / Y.at<double>(0, 2);

		vector<vector<BoundingBox>::iterator> enclosingBoxes; // pointers to all bounding boxes which enclose the current Lidar point
		for (vector<BoundingBox>::iterator it2 = boundingBoxes.begin(); it2 != boundingBoxes.end(); ++it2)
		{
			// shrink current bounding box slightly to avoid having too many outlier points around the edges
			cv::Rect smallerBox;
			smallerBox.x = (*it2).roi.x + shrinkFactor * (*it2).roi.width / 2.0;
			smallerBox.y = (*it2).roi.y + shrinkFactor * (*it2).roi.height / 2.0;
			smallerBox.width = (*it2).roi.width * (1 - shrinkFactor);
			smallerBox.height = (*it2).roi.height * (1 - shrinkFactor);

			// check wether point is within current bounding box
			if (smallerBox.contains(pt))
			{
				enclosingBoxes.push_back(it2);
			}

		} // eof loop over all bounding boxes

		// check wether point has been enclosed by one or by multiple boxes
		if (enclosingBoxes.size() == 1)
		{
			// add Lidar point to bounding box
			enclosingBoxes[0]->lidarPoints.push_back(*it1);
		}

	} // eof loop over all Lidar points
}

void show3DObjects(std::vector<BoundingBox> &boundingBoxes, cv::Size worldSize, cv::Size imageSize,
		bool bWait)
{
	// create topview image
	cv::Mat topviewImg(imageSize, CV_8UC3, cv::Scalar(255, 255, 255));

	for (auto it1 = boundingBoxes.begin(); it1 != boundingBoxes.end(); ++it1)
	{
		// create randomized color for current 3D object
		cv::RNG rng(it1->boxID);
		cv::Scalar currColor = cv::Scalar(rng.uniform(0, 150), rng.uniform(0, 150), rng.uniform(0, 150));

		// plot Lidar points into top view image
		int top = 1e8, left = 1e8, bottom = 0.0, right = 0.0;
		float xwmin = 1e8, ywmin = 1e8, ywmax = -1e8;
		for (auto it2 = it1->lidarPoints.begin(); it2 != it1->lidarPoints.end(); ++it2)
		{
			// world coordinates
			float xw = (*it2).x; // world position in m with x facing forward from sensor
			float yw = (*it2).y; // world position in m with y facing left from sensor
			xwmin = xwmin < xw ? xwmin : xw;
			ywmin = ywmin < yw ? ywmin : yw;
			ywmax = ywmax > yw ? ywmax : yw;

			// top-view coordinates
			int y = (-xw * imageSize.height / worldSize.height) + imageSize.height;
			int x = (-yw * imageSize.width / worldSize.width) + imageSize.width / 2;

			// find enclosing rectangle
			top = top < y ? top : y;
			left = left < x ? left : x;
			bottom = bottom > y ? bottom : y;
			right = right > x ? right : x;

			// draw individual point
			cv::circle(topviewImg, cv::Point(x, y), 4, currColor, -1);
		}

		// draw enclosing rectangle
		cv::rectangle(topviewImg, cv::Point(left, top), cv::Point(right, bottom), cv::Scalar(0, 0, 0), 2);

		// augment object with some key data
		char str1[200], str2[200];
		sprintf(str1, "id=%d, #pts=%d", it1->boxID, (int) it1->lidarPoints.size());
		putText(topviewImg, str1, cv::Point2f(left - 250, bottom + 50), cv::FONT_ITALIC, 2, currColor);
		sprintf(str2, "xmin=%2.2f m, yw=%2.2f m", xwmin, ywmax - ywmin);
		putText(topviewImg, str2, cv::Point2f(left - 250, bottom + 125), cv::FONT_ITALIC, 2, currColor);
	}

	// plot distance markers
	float lineSpacing = 2.0; // gap between distance markers
	int nMarkers = floor(worldSize.height / lineSpacing);
	for (size_t i = 0; i < nMarkers; ++i)
	{
		int y = (-(i * lineSpacing) * imageSize.height / worldSize.height) + imageSize.height;
		cv::line(topviewImg, cv::Point(0, y), cv::Point(imageSize.width, y), cv::Scalar(255, 0, 0));
	}

	// display image
	string windowName = "3D Objects";
	cv::namedWindow(windowName, 1);
	cv::imshow(windowName, topviewImg);

	if (bWait)
	{
		cv::waitKey(0); // wait for key to be pressed
	}
}

// associate a given bounding box with the keypoints it contains
void clusterKptMatchesWithROI(BoundingBox &boundingBox, std::vector<cv::KeyPoint> &kptsPrev,
		std::vector<cv::KeyPoint> &kptsCurr, std::vector<cv::DMatch> &kptMatches)
{
	// Student Code 1
	/*for (int it = 0; it < kptMatches.size(); it++)
	 {
	 if (boundingBox.roi.contains(kptsCurr[kptMatches[it].trainIdx].pt))
	 {
	 boundingBox.kptMatches.push_back(kptMatches[it]);
	 }
	 }*/
	for (cv::DMatch match : kptMatches)
	{
		if (boundingBox.roi.contains(kptsCurr[match.trainIdx].pt))
		{
			boundingBox.kptMatches.push_back(match);
		}
	}
}

// Compute time-to-collision (TTC) based on keypoint correspondences in successive images
void computeTTCCamera(std::vector<cv::KeyPoint> &kptsPrev, std::vector<cv::KeyPoint> &kptsCurr,
		std::vector<cv::DMatch> kptMatches, double frameRate, double &TTC, cv::Mat *visImg)
{
	// Student Code 2
	vector<double> distance_ratios;
	for (auto it_outer = kptMatches.begin(); it_outer != kptMatches.end() - 1; it_outer++)
	{
		cv::KeyPoint kpOuterCurr = kptsCurr.at(it_outer->trainIdx);
		cv::KeyPoint kpOuterPrev = kptsPrev.at(it_outer->queryIdx);

		for (auto it_inner = kptMatches.begin() + 1; it_inner != kptMatches.end(); it_inner++)
		{
			cv::KeyPoint kpInnerCurr = kptsCurr.at(it_inner->trainIdx);
			cv::KeyPoint kpInnerPrev = kptsPrev.at(it_inner->queryIdx);

			double distCurr = cv::norm(kpOuterCurr.pt - kpInnerCurr.pt);
			double distPrev = cv::norm(kpOuterPrev.pt - kpInnerPrev.pt);

			double minDist = 100.0;

			if (distPrev > std::numeric_limits<double>::epsilon() && distCurr >= minDist)
			{
				double distRatio = distCurr / distPrev;
				distance_ratios.push_back(distRatio);
			}
		}
	}

	if (distance_ratios.size() == 0)
	{
		TTC = std::numeric_limits<double>::quiet_NaN();
		return;
	}

	std::sort(distance_ratios.begin(), distance_ratios.end());
	double medianDistRatio = distance_ratios[distance_ratios.size() / 2];
	TTC = (-1.0 / frameRate) / (1 - medianDistRatio);
}
/*This is function to use as comparator for sorting two Lidarpoints
 * */
bool sortByX(const LidarPoint lp1, LidarPoint lp2)
{
	return lp1.x < lp2.x;
}
/*
 *The following used to calculate the TTC using Lidar pointers.
 */
void computeTTCLidar(std::vector<LidarPoint> &lidarPointsPrev, std::vector<LidarPoint> &lidarPointsCurr,
		double frameRate, double &TTC)
{

	std::sort(lidarPointsPrev.begin(), lidarPointsPrev.end(), sortByX);
	std::sort(lidarPointsCurr.begin(), lidarPointsCurr.end(), sortByX);
	/*Taking median point helped me to achieve removing outlier and reasonable TTC*/
	double d0 = lidarPointsPrev[lidarPointsPrev.size() / 2].x;
	double d1 = lidarPointsCurr[lidarPointsCurr.size() / 2].x;

	TTC = d1 * (1.0 / frameRate) / (d0 - d1);
}

void matchBoundingBoxes(std::map<int, int> &bbBestMatches, DataFrame &prevFrame, DataFrame &currFrame)
{
	std::multimap<int, int> mmap;
	int maxPrevBoxID = 0;
	std::vector<cv::DMatch> matches = currFrame.kptMatches;
	for (auto match : matches)
	{
		cv::KeyPoint prevKp = prevFrame.keypoints[match.queryIdx];
		cv::KeyPoint currKp = currFrame.keypoints[match.trainIdx];

		int prevBoxID = -1;
		int currBoxID = -1;

		// For each bounding box in the previous frame
		for (auto bbox : prevFrame.boundingBoxes)
		{
			if (bbox.roi.contains(prevKp.pt))
			{
				prevBoxID = bbox.boxID;
			}
		}

		// For each bounding box in the current frame
		for (auto bbox : currFrame.boundingBoxes)
		{
			if (bbox.roi.contains(currKp.pt))
			{
				currBoxID = bbox.boxID;
			}
		}

		// Add the containing boxID for each match to a multimap
		mmap.insert(
		{ currBoxID, prevBoxID });

		maxPrevBoxID = std::max(maxPrevBoxID, prevBoxID);
	}

	vector<int> currFrameBoxIDs;
	for (auto box : currFrame.boundingBoxes)
		currFrameBoxIDs.push_back(box.boxID);

	for (int curr_frm_box_id : currFrameBoxIDs)
	{

		auto rangePrevBoxIDs = mmap.equal_range(curr_frm_box_id);

		std::vector<int> counts(maxPrevBoxID + 1, 0);

		for (auto it = rangePrevBoxIDs.first; it != rangePrevBoxIDs.second; ++it)
		{
			if (-1 != (*it).second)
				counts[(*it).second] += 1;
		}

		int modeIndex = std::distance(counts.begin(), std::max_element(counts.begin(), counts.end()));

		bbBestMatches.insert(
		{ modeIndex, curr_frm_box_id });
	}
}
