#include "twitter.hh"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>
#include <queue>

void Twitter::postTweet(unsigned int user_id, unsigned int tweet_id)
{
    if (tweet_map_.find(user_id) == tweet_map_.end())
    {
        tweet_map_[user_id] = std::vector<Twitt>();
        // follow itself
        if (users_.find(user_id) == users_.end())
            users_[user_id] = std::vector<unsigned int>({user_id});
        else
            if (std::find(users_[user_id].begin(), users_[user_id].end(), user_id) == users_[user_id].end())
                users_[user_id].push_back(user_id);
    }
    tweet_map_[user_id].insert(tweet_map_[user_id].begin(), Twitt{tweet_id, stamp});
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
    auto followers_iter = users_.find(followee);
    if (followers_iter == users_.end())
        return;
    auto& followers = followers_iter->second;
    auto followers_it = std::find(followers.begin(), followers.end(), follower);
    if (followers_it != followers.end())
    {
        followers.erase(followers_it);
    }
}


std::vector<unsigned int> Twitter::getNewsFeed(unsigned int user_id)
{
    auto cmp = [](Twitt left, Twitt right){return left.timestamp < right.timestamp;};
    std::priority_queue<Twitt, std::vector<Twitt>, decltype(cmp)> res(cmp);
    if (users_.find(user_id) != users_.end())
    {
        for (auto follow : users_[user_id])
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
    std::vector<unsigned int> final_res; 
    while (final_res.size() < 10 && !res.empty())
    {
        auto top = res.top();
        final_res.push_back(top.id);
        res.pop();
    }
    return final_res;
}

void Twitter::dumpState()
{
    std::cout << "Tweets:\n";
    for (auto& tweets_by_id : tweet_map_)
    {
        std::cout << tweets_by_id.first << " : ";
        for (auto& tweets : tweets_by_id.second)
            std::cout << "(" << tweets.id << "," << tweets.timestamp << ")"
                      << ", ";
        std::cout << "\n";
    }
    std::cout << "Users:\n";
    for (auto& follower_by_user : users_)
    {
        std::cout << follower_by_user.first << " : ";
        for (auto& follower : follower_by_user.second)
            std::cout << follower << ", ";
        std::cout << "\n";
    }
}
