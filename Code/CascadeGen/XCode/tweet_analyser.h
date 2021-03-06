#ifndef tweet_analyser_h
#define tweet_analyser_h

#include "tweet.h"
#include "cascade.h"
#include "utility.h"

typedef enum {OR = 0, AND = 1, NOT = 2} tweetAnalyserKeywordSearchOption;

/* TweetAnalyser class */

class TweetAnalyser {
public:
    TweetAnalyser();
    
    ~TweetAnalyser();
    
    TweetAnalyser operator=(const TweetAnalyser& tc);
    
    // read in a parsed tweet data file
    vector<Tweet> readParsedTweetDataFromFile(const string& parsedTweetDataFilename) const;
    
    // note: NEED to sort Tweet objects by screenNameId !!!
    // return all distinct screen names with number of tweets sent from each screen name, as well as id's of all tweets sent
    vector<TweetScreenNameOccurenceCacheItem> extractAmountTweetDataForAllScreenNames(const vector<Tweet>& tweetData) const;
    
    // return, for each keyword, the number of tweets that were sent that contained that keyword, as well as id's of all tweets sent
    vector<TweetKeywordOccurenceCacheItem> extractAmountTweetDataForKeywords(const vector<Tweet>& tweetData, const vector<string>& keywords) const;
    
    // return, for each screen name, all tweets sent by the account
    vector<Tweet> extractSpecificScreenNameTweetData(const vector<Tweet>& tweetData, const vector<string>& screenNames) const;
    
    // return, for each screen name id, all tweets sent by the account
    vector<Tweet> extractSpecificScreenNameTweetData(const vector<Tweet>& tweetData, const vector<int>& screenNameIds) const;
    
    // return, for a combination of the keywords (depending on the option), all tweets containing the combination
    vector<Tweet> extractKeywordsContainedTweetData(const vector<Tweet>& tweetData, const vector<string>& keywords, const tweetAnalyserKeywordSearchOption& option) const;
    
    // return all tweets corresponding to the ids specified.
    vector<Tweet> extractSpecificIdTweetData(const vector<Tweet>& tweetData, const vector<int>& tweetIds) const;
    
    // return tweets that have been @username mentioned by and to users, that have actively tweeted, and messages contains combination of the keywords (depending on the option),
    vector<TweetKeywordUsernameMentionedCacheItem> extractKeywordsContainedUsernameMentionedTweetData(const vector<Tweet>& tweetData, const vector<string>& keywords, const tweetAnalyserKeywordSearchOption& option) const;
    
    // given tweet data and a list of keywords, write all cascades generated to an output file
    void writeCascadesDataToFile(const string& casacdesDataFilename, const vector<Tweet>& tweetData, const vector<string>& keywords) const;
    
private:
    
    // return only the first infections for each twitter account from all tweets sent
    vector<Tweet> extractOnlyFirstInfectionsTweetData(const vector<Tweet>& tweetData) const;
    
    // return a list of twitter accounts that sent tweets within the tweet data specified
    vector<TwitterAccount> generateTwitterAccounts(const vector<Tweet>& tweetData) const;
    
    // generate a single cascade from tweet data based upon a keyword
    Cascade generateCascade(const vector<Tweet>& tweetData, const string& keyword) const;
    
    // generate a list of cascades from tweet data based upon a list of keywords
    vector<Cascade> generateCascades(const vector<Tweet>& tweetData, const vector<string>& keywords) const;
    
    // return a list of individual mentions from an input string
    vector<string> extractMentionsAndStoreFromString(const string& mentions) const;
    
    const string mentionPostMentionAsString = ";";
};

#endif