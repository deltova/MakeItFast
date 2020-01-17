#include "twitter.hh"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>
#include <queue>

void Twitter::postTweet(unsigned int userid, unsigned int tweetid)
{
    if (tweet_map_.find(userid) == tweet_map_.end())
    {
        tweet_map_[userid] = std::vector<Twitt>();
    }
    tweet_map_[userid].insert(tweet_map_[userid].begin(), Twitt{tweetid, stamp});
    stamp++;
}

void Twitter::follow(unsigned int followee, unsigned int follower)
{
    if (followee == follower)
        return;
    if (users_.find(followee) == users_.end())
    {
        users_[followee] = std::vector<unsigned int>();
    }
    auto& followers = users_[followee];
    if (std::find(followers.begin(), followers.end(), follower) == followers.end())
        users_[followee].push_back(follower);
}

void Twitter::unfollow(unsigned int followee, unsigned int follower)
{
    if (followee == follower)
        return;
    auto followersIter = users_.find(followee);
    if (followersIter == users_.end())
        return;
    auto& followers = followersIter->second;
    auto followerIt = std::find(followers.begin(), followers.end(), follower);
    if (followerIt != followers.end())
    {
        followers.erase(followerIt);
    }
}

struct QueueCmp{
    bool operator()(Twitt &s1,Twitt &s2){
            return s1.timestamp<s2.timestamp;
}
};
std::vector<unsigned int> Twitter::getNewsFeed(unsigned int userid)
{
    std::priority_queue<Twitt, std::vector<Twitt>, QueueCmp> res;
    if (tweet_map_.find(userid) != tweet_map_.end())
    {
        auto &ownTweet = tweet_map_[userid];
        auto end = ownTweet.size() > 10 ? ownTweet.begin() + 10 : ownTweet.end();
        for (auto it = ownTweet.begin(); it !=  end; ++it)
        {
            res.push(*it);
        }
    }
    if (users_.find(userid) != users_.end())
    {
        std::vector<unsigned int> &following = users_[userid];
        for (auto follow : following)
        {
            if (tweet_map_.find(follow) != tweet_map_.end())
            {
                auto &tweets = tweet_map_[follow];
                auto end = tweets.size() > 10 ? tweets.begin() + 10 : tweets.end();
                for (auto it = tweets.begin(); it !=  end; ++it)
                {
                    res.push(*it);
                }
            }
        }
    }
    std::vector<unsigned int> finalRes; 
    while (finalRes.size() < 10 && !res.empty())
    {
        auto top = res.top();
        finalRes.push_back(top.id);
        res.pop();
    }
    return finalRes;
}

void Twitter::dump_state()
{
    std::cout << "Tweets:\n";
    for (auto& tweetsById : tweet_map_)
    {
        std::cout << tweetsById.first << " : ";
        for (auto& tweets : tweetsById.second)
            std::cout << "(" << tweets.id << "," << tweets.timestamp << ")"
                      << ", ";
        std::cout << "\n";
    }
    std::cout << "Users:\n";
    for (auto& followerByUser : users_)
    {
        std::cout << followerByUser.first << " : ";
        for (auto& follower : followerByUser.second)
            std::cout << follower << ", ";
        std::cout << "\n";
    }
}
