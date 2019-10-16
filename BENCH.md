16/10:
    114 ms
16/10:
    64 ms
    enable the CPU perfomance mode and reorganize the bench to not count the parsing
16/10:
    35 ms
    In the getNewsFeed function we use to get all the 10 last tweets per user and then sort everything
    Now we add 10 last per user then sort then keep the last 10 tweets.
16/10:
    30 ms
    Instead of comibining the current last 10 twitts and the last 10 twitts of the current user then sorting
    the vector using std::sort.
    We now use the std::implace_merge
