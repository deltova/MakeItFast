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
        // follow itself
        if (users_.find(userid) == users_.end())
            users_[userid] = std::vector<unsigned int>({userid});
        else
            if (std::find(users_[userid].begin(), users_[userid].end(), userid) == users_[userid].end())
                users_[userid].push_back(userid);
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


std::vector<unsigned int> Twitter::getNewsFeed(unsigned int userid)
{
    auto cmp = [](Twitt left, Twitt right){return left.timestamp < right.timestamp;};
    std::priority_queue<Twitt, std::vector<Twitt>, decltype(cmp)> res(cmp);
    if (users_.find(userid) != users_.end())
    {
        for (auto follow : users_[userid])
        {
            if (tweet_map_.find(follow) != tweet_map_.end())
            {
                auto &tweets = tweet_map_[follow];
                auto end = tweets.size() > 10 ? tweets.begin() + 10 : tweets.end();
                for (auto it = tweets.begin(); it != end; ++it)
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
