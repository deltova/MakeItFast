#! /usr/bin/python
BUILD_PATH = "../build/"
LIBNAME = "libTwitter.so"
import sys
sys.path.append(BUILD_PATH)
import ctypes
import os
ctypes.CDLL(BUILD_PATH + LIBNAME, mode=os.RTLD_LAZY) 
from twitwi import Twitter

import json
from random import randint
import time

class TwitterRef:
    def __init__(self):
        self.tweetMap = {}
        self.users = {}

    def postTweet(self, userId, tweetId):
        if userId in self.tweetMap:
            self.tweetMap[userId].insert(0, (tweetId, time.time()))
        else:
            self.tweetMap[userId] = [(tweetId, time.time())]

    def getNewsFeed(self, userId):
        tweets = self.tweetMap[userId][0:10] if userId in self.tweetMap else []
        if userId not in self.users: return [x[0] for x in tweets ]
        followees = self.users[userId]
        if followees is None: return [x[0] for x in tweets ]
        for followee in followees:
            if followee in self.tweetMap:
                tweets += self.tweetMap[followee][0:10]
        lastTweets = sorted(tweets, key=lambda x: x[1], reverse=True)[0:10]
        return [x[0] for x in lastTweets ]
            
    def follow(self, followerId, followeeId):
        if followerId == followeeId:
            return
        if followerId in self.users and self.users[followerId] is not None:
            self.users[followerId].add(followeeId)
        else:
            self.users[followerId] = set()
            self.users[followerId].add(followeeId)

    def unfollow(self, followerId, followeeId):
        if followerId == followeeId:
            return
        if followerId in self.users:
            if self.users[followerId] is None: return
            if followeeId in self.users[followerId]:
                self.users[followerId].remove(followeeId)

class Wrapper:
    def __init__(self):
        self.twitterRef = TwitterRef()
        self.twitter = Twitter()
    def exec(self, input):
        if input[0] == 3:
            return self.twitter.getNewsFeed(input[1]), self.twitterRef.getNewsFeed(input[1])
        elif input[0] == 0:
            self.twitter.follow(input[1], input[2])
            self.twitterRef.follow(input[1], input[2])
        elif input[0] == 1:
            self.twitter.unfollow(input[1], input[2])
            self.twitterRef.unfollow(input[1], input[2])
        elif input[0] == 2:
            self.twitterRef.postTweet(input[1], input[2])
            self.twitter.postTweet(input[1], input[2])


def generate_array(nbAction):
    res = [] 
    for i in range(randint(0, nbAction)):
        action = randint(0, 3)
        if action == 3:
            res.append((action, randint(0, 100)))
        else:
            res.append((action, randint(0, 100), randint(0, 100)))
    return res

def test(actions=None):
    wrapper = Wrapper()
    if actions is None:
        actions = generate_array(100000)
    with open("actions", "w") as f:
        json.dump(actions, f)
    for action in actions:
        if action[0] == 3:
            res = wrapper.exec(action)
            ref = res[1]
            tested = [elm for elm in res[0]]
            assert ref == tested, (ref, tested)
        else:
            wrapper.exec(action)
if __name__ == "__main__":
    if len(sys.argv) > 1:
        with open(sys.argv[1], "r") as f:
            actions = json.load(f)
            test(actions)
    else:
        test()
    print("All generated tests passed")
