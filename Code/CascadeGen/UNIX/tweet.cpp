#include "tweet.h"

/* Twitter Account class methods */

TwitterAccount::TwitterAccount() {}

TwitterAccount::~TwitterAccount() {}

TwitterAccount::TwitterAccount(const TwitterAccount& tc):id(tc.id), screenName(tc.screenName) {}

TwitterAccount::TwitterAccount(int id, string screenName) {
    this->id = id;
    this->screenName = screenName;
}

TwitterAccount TwitterAccount::operator=(const TwitterAccount& tc) {
    if (this == &tc) {
        return *this;
    }
    else {
        id = tc.id;
        screenName = tc.screenName;
        return *this;
    }
}

void TwitterAccount::setId(const int id) {
    this->id = id;
}

int TwitterAccount::getId() const {
    return id;
}

void TwitterAccount::setScreenName (const string screenName) {
    this->screenName = screenName;
}

string TwitterAccount::getScreenName() const {
    return screenName;
}

string TwitterAccount::toString() const {
    return convertIntToString(id) + "," + screenName;
}

ostream& operator<<(ostream& os, const TwitterAccount& obj) {
    os << obj.toString();
    return os;
}


/* Tweet class methods */

Tweet::Tweet() {
    timeStampFormat = "%a %b %d %T %z %Y";
}

Tweet::~Tweet() {
    mentions.clear();
}

Tweet::Tweet(const Tweet& tc):id(tc.id), account(tc.account), timeStamp(tc.timeStamp), content(tc.content), mentions(tc.mentions) {
    timeStampFormat = "%a %b %d %T %z %Y";
}

Tweet::Tweet(int id, TwitterAccount account, string timeStamp, string content, vector<string> mentions) {
    this->id = id;
    this->account = account;
    this->timeStamp = timeStamp;
    this->content = content;
    this->mentions = mentions;
    timeStampFormat = "%a %b %d %T %z %Y";
}

Tweet Tweet::operator=(const Tweet& tc) {
    if (this == &tc) {
        return *this;
    }
    else {
        id = tc.id;
        account = tc.account;
        timeStamp = tc.timeStamp;
        content = tc.content;
        mentions = tc.mentions;
        timeStampFormat = "%a %b %d %T %z %Y";
        return *this;
    }
}

void Tweet::setId(const int id) {
    this->id = id;
}

int Tweet::getId() const {
    return id;
}

void Tweet::setAccount(const TwitterAccount account) {
    this->account = account;
}

TwitterAccount Tweet::getAccount() const {
    return account;
}

void Tweet::setTimeStamp(const string timeStamp) {
    this->timeStamp = timeStamp;
}

string Tweet::getTimeStamp() const {
    return timeStamp;
}

void Tweet::setContent(const string content) {
    this->content = content;
}

string Tweet::getContent() const {
    return content;
}

void Tweet::setMentions(const vector<string> mentions) {
    this->mentions = mentions;
}

vector<string> Tweet::getMentions() const {
    return mentions;
}

string Tweet::getTimeStampFormat() const {
    return timeStampFormat;
}

string Tweet::toString() const {
    string allMentions = "";
    for (int i = 0; i < mentions.size(); i++) {
        allMentions += mentions.at(i) + ";";
    }
    return convertIntToString(id) + "\n" + account.getScreenName() + "\n" + convertIntToString(account.getId()) + "\n" + timeStamp + "\n" + content + "\n" + allMentions;
}

bool Tweet::compareTimeStamps(const Tweet& tweet2) const {
    string timeStamp1 = timeStamp;
    string timeStamp2 = tweet2.timeStamp;
    time_t t1, t2;
    struct tm tm1, tm2;
    strptime(timeStamp1.c_str(), timeStampFormat.c_str(), &tm1);
    strptime(timeStamp2.c_str(), timeStampFormat.c_str(), &tm2);
    t1 = mktime(&tm1);
    t2 = mktime(&tm2);
    return (difftime(t1, t2) > 0.0) ? false : true;
}

bool Tweet::compareScreenNames(const Tweet& tweet2) const {
    string screenName1 = account.getScreenName();
    string screenName2 = tweet2.account.getScreenName();
    transform(screenName1.begin(), screenName1.end(), screenName1.begin(), ::tolower);
    transform(screenName2.begin(), screenName2.end(), screenName2.begin(), ::tolower);
    return screenName1 < screenName2;
}

bool Tweet::compareIds(const Tweet& tweet2) const {
    int id1 = id;
    int id2 = tweet2.id;
    return id1 < id2;
}

bool Tweet::compareScreenNameIds(const Tweet& tweet2) const {
    int id1 = account.getId();
    int id2 = tweet2.account.getId();
    return id1 < id2;
}

bool Tweet::operator<(const Tweet& tweet2) const {
    return compareScreenNameIds(tweet2);
}

ostream& operator<<(ostream& os, const Tweet& obj) {
    os << obj.toString();
    return os;
}


/* TweetScreenNameOccurenceCacheItem class methods */

TweetScreenNameOccurenceCacheItem::TweetScreenNameOccurenceCacheItem() {}

TweetScreenNameOccurenceCacheItem::~TweetScreenNameOccurenceCacheItem() {
    tweetIds.clear();
}

TweetScreenNameOccurenceCacheItem TweetScreenNameOccurenceCacheItem::operator=(const TweetScreenNameOccurenceCacheItem& tc) {
    if (this == &tc) {
        return *this;
    }
    else {
        account = tc.account;
        noTweetsSent = tc.noTweetsSent;
        tweetIds = tc.tweetIds;
        return *this;
    }
}

TweetScreenNameOccurenceCacheItem::TweetScreenNameOccurenceCacheItem(TwitterAccount account, int noTweetsSent, vector<int> tweetIds) {
    this->account = account;
    this->noTweetsSent = noTweetsSent;
    this->tweetIds = tweetIds;
}

TwitterAccount TweetScreenNameOccurenceCacheItem::getAccount() const {
    return account;
}

int TweetScreenNameOccurenceCacheItem::getNoTweetsSent() const {
    return noTweetsSent;
}

vector<int> TweetScreenNameOccurenceCacheItem::getTweetIds() const {
    return tweetIds;
}

void TweetScreenNameOccurenceCacheItem::setAccount(const TwitterAccount& account) {
    this->account = account;
}

void TweetScreenNameOccurenceCacheItem::setNoTweetsSent(const int noTweetsSent) {
    this->noTweetsSent = noTweetsSent;
}

void TweetScreenNameOccurenceCacheItem::setTweetIds(const vector<int> tweetIds) {
    this->tweetIds = tweetIds;
}

void TweetScreenNameOccurenceCacheItem::incrementNoTweetsSent() {
    noTweetsSent++;
}

string TweetScreenNameOccurenceCacheItem::toString() const {
    stringstream allTweetsIds_ss;
    for (int i = 0; i < tweetIds.size(); i++) {
        allTweetsIds_ss << tweetIds.at(i);
        allTweetsIds_ss << ";";
    }
    return account.toString() + ", " + convertIntToString(noTweetsSent)+ ", " + allTweetsIds_ss.str();
}

bool TweetScreenNameOccurenceCacheItem::compareNoTweetsSent(const TweetScreenNameOccurenceCacheItem& tweetScreenNameOccurenceCacheItem2) const {
    return noTweetsSent < tweetScreenNameOccurenceCacheItem2.noTweetsSent;
}

bool TweetScreenNameOccurenceCacheItem::compareScreenNames(const TweetScreenNameOccurenceCacheItem& tweetScreenNameOccurenceCacheItem2) const {
    string screenName1 = account.getScreenName();
    string screenName2 = tweetScreenNameOccurenceCacheItem2.account.getScreenName();
    transform(screenName1.begin(), screenName1.end(), screenName1.begin(), ::tolower);
    transform(screenName2.begin(), screenName2.end(), screenName2.begin(), ::tolower);
    return screenName1 < screenName2;
}

bool TweetScreenNameOccurenceCacheItem::compareScreenNameIds(const TweetScreenNameOccurenceCacheItem& tweetScreenNameOccurenceCacheItem2) const {
    return account.getId() < tweetScreenNameOccurenceCacheItem2.account.getId();
}

bool TweetScreenNameOccurenceCacheItem::operator<(const TweetScreenNameOccurenceCacheItem& tweetScreenNameOccurenceCacheItem2) const {
    return compareScreenNameIds(tweetScreenNameOccurenceCacheItem2);
}

ostream& operator<<(ostream& os, const TweetScreenNameOccurenceCacheItem& obj) {
    os << obj.toString();
    return os;
}


/* TweetKeywordOccurenceCacheItem class methods */

TweetKeywordOccurenceCacheItem::TweetKeywordOccurenceCacheItem() {}

TweetKeywordOccurenceCacheItem::~TweetKeywordOccurenceCacheItem() {
    tweetIds.clear();
}

TweetKeywordOccurenceCacheItem TweetKeywordOccurenceCacheItem::operator=(const TweetKeywordOccurenceCacheItem& tc) {
    if (this == &tc) {
        return *this;
    }
    else {
        keyword = tc.keyword;
        noTweetsSent= tc.noTweetsSent;
        tweetIds = tc.tweetIds;
        return *this;
    }
}

TweetKeywordOccurenceCacheItem::TweetKeywordOccurenceCacheItem(string keyword, int noTweetsSent, vector<int> tweetIds) {
    this->keyword = keyword;
    this->noTweetsSent = noTweetsSent;
    this->tweetIds = tweetIds;
}

string TweetKeywordOccurenceCacheItem::getKeyword() const {
    return keyword;
}

int TweetKeywordOccurenceCacheItem::getNoTweetsSent() const {
    return noTweetsSent;
}

vector<int> TweetKeywordOccurenceCacheItem::getTweetIds() const {
    return tweetIds;
}

void TweetKeywordOccurenceCacheItem::setKeyword(const string keyword) {
    this->keyword = keyword;
}

void TweetKeywordOccurenceCacheItem::setNoTweetsSent(const int noTweetsSent) {
    this->noTweetsSent = noTweetsSent;
}

void TweetKeywordOccurenceCacheItem::setTweetIds(const vector<int> tweetIds) {
    this->tweetIds = tweetIds;
}

void TweetKeywordOccurenceCacheItem::incrementNoTweetsSent() {
    noTweetsSent++;
}

string TweetKeywordOccurenceCacheItem::toString() const {
    stringstream allTweetsIds_ss;
    for (int i = 0; i < tweetIds.size(); i++) {
        allTweetsIds_ss << tweetIds.at(i);
        allTweetsIds_ss << ";";
    }
    return keyword + ", " + convertIntToString(noTweetsSent) + ", " + allTweetsIds_ss.str();
}

bool TweetKeywordOccurenceCacheItem::compareNoTweetsSent(const TweetKeywordOccurenceCacheItem& tweetKeywordOccurenceCacheItem2) const {
    return noTweetsSent < tweetKeywordOccurenceCacheItem2.noTweetsSent;
}

bool TweetKeywordOccurenceCacheItem::compareKeywords(const TweetKeywordOccurenceCacheItem& tweetKeywordOccurenceCacheItem2) const {
    string keyword1 = keyword;
    string keyword2 = tweetKeywordOccurenceCacheItem2.keyword;
    transform(keyword1.begin(), keyword1.end(), keyword1.begin(), ::tolower);
    transform(keyword2.begin(), keyword2.end(), keyword2.begin(), ::tolower);
    return keyword1 < keyword2;
}

bool TweetKeywordOccurenceCacheItem::operator<(const TweetKeywordOccurenceCacheItem& tweetKeywordOccurenceCacheItem2) const {
    return compareNoTweetsSent(tweetKeywordOccurenceCacheItem2);
}

ostream& operator<<(ostream& os, const TweetKeywordOccurenceCacheItem& obj) {
    os << obj.toString();
    return os;
}


/* TweetKeywordUsernameMentionedCacheItem class methods */

TweetKeywordUsernameMentionedCacheItem::TweetKeywordUsernameMentionedCacheItem() {}

TweetKeywordUsernameMentionedCacheItem::~TweetKeywordUsernameMentionedCacheItem() {}

TweetKeywordUsernameMentionedCacheItem TweetKeywordUsernameMentionedCacheItem::operator=(const TweetKeywordUsernameMentionedCacheItem& tc) {
    if (this == &tc) {
        return *this;
    }
    else {
        initialTweet = tc.initialTweet;
        influencedTweet= tc.influencedTweet;
        return *this;
    }
}

TweetKeywordUsernameMentionedCacheItem::TweetKeywordUsernameMentionedCacheItem(Tweet initialTweet, Tweet influencedTweet) {
    this->initialTweet = initialTweet;
    this->influencedTweet = influencedTweet;
}

Tweet TweetKeywordUsernameMentionedCacheItem::getInitialTweet() const {
    return initialTweet;
}

Tweet TweetKeywordUsernameMentionedCacheItem::getInfluencedTweet() const {
    return influencedTweet;
}

void TweetKeywordUsernameMentionedCacheItem::setInitialTweet(const Tweet& initialTweet) {
    this->initialTweet = initialTweet;
}

void TweetKeywordUsernameMentionedCacheItem::setInfluencedTweet(const Tweet& influencedTweet) {
    this->influencedTweet = influencedTweet;
}

string TweetKeywordUsernameMentionedCacheItem::toString() const {
    return initialTweet.toString() + "\n" + influencedTweet.toString();
}

ostream& operator<<(ostream& os, const TweetKeywordUsernameMentionedCacheItem& obj) {
    os << obj.toString();
    return os;
}
