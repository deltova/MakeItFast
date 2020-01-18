#pragma once
#include <ctime>
#include <unordered_map>
#include <vector>

struct Twitt
{
    unsigned int id;
    unsigned long long timestamp;
};

class Twitter
{
  public:
    void postTweet(unsigned int user_id, unsigned int tweet_id);
    void follow(unsigned int followee, unsigned int follower);
    void unfollow(unsigned int followee, unsigned int follower);
    std::vector<unsigned int> getNewsFeed(unsigned int followee);

  private:
    void dumpState();
    std::unordered_map<unsigned int, std::vector<unsigned int>> users_;
    std::unordered_map<unsigned int, std::vector<Twitt>> tweet_map_;
    unsigned long long stamp = 0;
};
