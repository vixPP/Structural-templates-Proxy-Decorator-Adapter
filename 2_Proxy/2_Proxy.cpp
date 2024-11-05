#include <iostream>
#include <map>
#include <string>

class VeryHeavyDatabase
{
public:
    std::string GetData(const std::string& key) const noexcept
    {
        return "Very Big Data String: " + key;
    }
};

class CacheProxyDB : VeryHeavyDatabase
{
public:
    explicit CacheProxyDB(VeryHeavyDatabase* real_obj) : real_db_(real_obj) {}
    std::string GetData(const std::string& key) noexcept
    {
        if (cache_.find(key) == cache_.end())
        {
            std::cout << "Get from real object \n";
            cache_[key] = real_db_->GetData(key);
        }
        else
        {
            std::cout << "Get from cache\n";
        }
        return cache_.at(key);
    }


private:
    std::map<std::string, std::string> cache_;
    VeryHeavyDatabase* real_db_;
};

class OneShotDB : VeryHeavyDatabase
{
public:
    explicit OneShotDB(VeryHeavyDatabase* real_obj, size_t shots = 2) : real_db_(real_obj), shots_remaining_(shots){}
    
    std::string GetData(const std::string& key)
    {
        if(shots_remaining_ > 0)
        {
            shots_remaining_--;

            return real_db_->GetData(key);
        }
        else
        {
            return "error";
        }
    }

private:

    VeryHeavyDatabase* real_db_;
    size_t shots_remaining_;
};

int main()
{
    auto real_db = VeryHeavyDatabase();
    //auto cache_db = CacheProxyDB(std::addressof(real_db));
    //std::cout << cache_db.GetData("key") << std::endl;
    //std::cout << cache_db.GetData("key") << std::endl;

    auto limit_db = OneShotDB(std::addressof(real_db));
    std::cout << limit_db.GetData("key") << std::endl;
    std::cout << limit_db.GetData("key") << std::endl;
    std::cout << limit_db.GetData("key") << std::endl;
    std::cout << limit_db.GetData("key") << std::endl;

    return EXIT_SUCCESS;
}
