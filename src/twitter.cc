#include "twitter.hh"
#include <algorithm>

void Twitter::postTweet(unsigned int userid, unsigned int tweetid)
{
    std::time_t currentTime = std::time(nullptr);
    tweet_map_.try_emplace(userid, std::vector<Twitt>());
    std::vector<Twitt> tweets = tweet_map_.find(userid)->second;
    tweets.insert(tweets.begin(), Twitt{tweetid, currentTime});
}

void Twitter::follow(unsigned int followee, unsigned int follower)
{
    users_.try_emplace(followee, std::vector<unsigned int>());
    auto followers = users_[followee];
    if (std::find(followers.begin(), followers.end(), follower) == followers.end())
    {
        followers.push_back(follower);
    }
}

void Twitter::unfollow(unsigned int followee, unsigned int follower)
{
    auto followersIter = users_.find(followee);
    if (followersIter == users_.end())
        return;
    auto followers = followersIter->second;
    auto followerIt = std::find(followers.begin(), followers.end(), follower);
    if (followerIt != followers.end())
    {
        followers.erase(followerIt);
    }
}

std::vector<unsigned int> Twitter::getNewsFeed(unsigned int userid)
{
    std::vector<Twitt> res;
    if (tweet_map_.find(userid) != tweet_map_.end())
    {
        auto ownTweet = tweet_map_[userid];
        res = std::vector<Twitt>(ownTweet.begin(), ownTweet.begin() + 10);
    }
    if (users_.find(userid) != users_.end())
    {
        std::vector<unsigned int> following = users_[userid];
        for (auto follow : following)
        {
            if (tweet_map_.find(follow) != tweet_map_.end())
            {
                auto tweets = tweet_map_[follow];
                res.insert(res.end(), tweets.begin(), tweets.begin() + 10);
            }
        }
    }
    std::sort(res.begin(), res.end(), [](Twitt a, Twitt b) { return a.timestamp < b.timestamp; });
    std::vector<unsigned int> finalRes = {};
    for (auto it = res.begin(); it != res.begin() + 10 && it != res.end(); it++)
    {
        finalRes.push_back(it->id);
    }
    return finalRes;
}
