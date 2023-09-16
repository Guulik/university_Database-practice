#include <type_traits> 
#include <functional>

#include <cstring>
#include <string>
#include <vector>

#include "iostream"
#include <cmath>

#include <cstdlib>

struct  Data
{
    bool isDeleted;
};

template<typename TStruct, typename = std::enable_if<std::is_base_of<Data, TStruct>::value>>
class Database{
private:
    TStruct* _dataArray;
    std::string _databaseName;
    int _databaseSize;

    void NodeSwap(TStruct* a_ptr, TStruct* b_ptr){
        TStruct* temp = a_ptr;
        *a_ptr = *b_ptr;
        *b_ptr = *temp;
    }

public: 
    Database(const std::string& dataBaseName, int size) {
        _databaseName = dataBaseName;

        _dataArray = new TStruct[size];
        _databaseSize = size;

        for (size_t i = 0; i < size; i++)
            _dataArray[i].isDeleted = true;
    }

    ~Database() {
        delete[] _dataArray;
    }

   
    void Delete(int index){
        if (index<_databaseSize)
            _dataArray[index].isDeleted = true;
        else return;
    }

    int FindEmpty(){
        for (int index = 0; index < _databaseSize; index++){
            if (_dataArray[index].isDeleted)
                return index;
        }
        return -1;
    }

    void Add(int index, TStruct data){
        _dataArray[index] = data;
        _dataArray[index].isDeleted = false;
    }


    TStruct Get(int index){
        return index<_databaseSize&&index>=0 ? _dataArray[index] : *new TStruct();
    }

    std::vector<TStruct> GetAll(){
        std::vector<TStruct> allElements;
        for (size_t i = 0; i<_databaseSize; i++){
            if (!_dataArray[i].isDeleted)
                allElements.push_back(_dataArray[i]);
        }
        return allElements;
    }

    template<typename TValue, typename TFunction>
    int FindNearest(TValue valueToCompare, TFunction selectorFunction){
        if constexpr (std::is_same<TValue, int>::value){
            int indexOfNearestElement = -1;
            int minimalDiff = INT_MAX;

            for (size_t i = 0; i<_databaseSize; i++){
                if (!_dataArray[i].isDeleted){
                    int valueDiff = abs(selectorFunction(_dataArray[i]) - valueToCompare);
                    if(valueDiff < minimalDiff){
                        minimalDiff = valueDiff;
                        indexOfNearestElement = i;
                    }
                }
            }
            return indexOfNearestElement;
        }

        if constexpr (std::is_same<TValue, std::string>::value){
            for (size_t i = 0; i<_databaseSize; i++){

                size_t pos = selectorFunction(_dataArray[i]).find(valueToCompare);
                if (!_dataArray[i].isDeleted
                    && pos !=std::string::npos){
                        return i;
                    }
            }
        }
        return -1;
    }

};
