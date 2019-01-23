#ifndef SLOW_MOTION_SEQUENCE_H_
#define SLOW_MOTION_SEQUENCE_H_

#include <list>
#include <string>
#include "opencv2/opencv.hpp"

namespace sequence {

class Sequence {
 public:

  // Calls LoadVideo to load the video from <video_path> into a sequence.
  // Throws a LoadVideoFailException exception if the load fails.
  Sequence(std::string video_path);

  // Accessors and mutators
  const std::list<cv::Mat> get_frames() { return this->frames; }
  void push_back(cv::Mat frame) { this->frames.push_back(frame); }
  bool is_empty() { return this->frames.empty(); }

  // Loads the video from <video_path> into a sequence of frames.
  // Throws a LoadVideoFailException exception if the load fails.
  // Throws a VideoLoadedException exception if the sequence is already
  // populated.
  void LoadVideo(std::string video_path);

  // Writes the frame sequence as an .MP4 to <video_path>.
  // Throws a WriteVideoException exception if the write fails.
  void WriteVideo(std::string video_path);

  // Displays the video to the user.
  void DisplayVideo();

  struct VideoLoadedException : public std::exception {
    const char * what() const throw () {
      return " Could not load target video to Sequence because the sequence \
              \n already contains frames.";
    }
  };

 private:
  // Frame interpolation requires multiple inserts, which are O(1) for lists.
  std::list<cv::Mat> frames;
};

}  // namespace sequence

#endif  // SLOW_MOTION_SEQUENCE_H_