#pragma once
#include <ctime>
#include <map>
#include <vector>

struct Twitt {
  unsigned int id;
  time_t timestamp;
};

class Twitter {
public:
  void postTweet(unsigned int userid, unsigned int tweetid);
  void follow(unsigned int followee, unsigned int follower);
  void unfollow(unsigned int followee, unsigned int follower);
  std::vector<unsigned int> getNewsFeed(unsigned int followee);

private:
  std::map<unsigned int, std::vector<unsigned int>> users_;
  std::map<unsigned int, std::vector<Twitt>> tweet_map_;
};
