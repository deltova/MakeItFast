import pybindgen
from pybindgen import param

def generate(file_):
    mod = pybindgen.Module('twitter')
    mod.add_include('"../src/twitter.hh"')
    mod.add_container('std::vector<unsigned int>', 'unsigned int', 'vector') # declare a container only once
    klass = mod.add_class('Twitter')
    klass.add_constructor([])
    klass.add_method('postTweet', None, [param('unsigned int', 'userid'),
                                         param('unsigned int', 'tweetid')])
    klass.add_method('follow', None, [param('unsigned int', 'followee'),
                                      param('unsigned int', 'follower')])
    klass.add_method('unfollow', None, [param('unsigned int', 'followee'),
                                      param('unsigned int', 'follower')])
    klass.add_method('getNewsFeed', "std::vector<unsigned int>", [param('unsigned int', 'followee')])
    mod.generate(file_)

