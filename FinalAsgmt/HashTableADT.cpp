#include <iostream> // <string>이 내장
using namespace std;

/* 초기 ADT를 객체로 생성할때 hash table을 운용하기 위한 배열 길이를 정해준 후,
 * key로 string이 들어오게 됩니다.
 * string의 경우 각 자리의(char) ascii 코드 2자리를 경계 접기로 더해준 후 배열 길이를 초과하지 않는 나머지를 구해서 이를 배열의 인덱스로 사용합니다.
 * int 배열의 특정 인덱스의 값이 비어있는 것을 나타내기 위해 정수의 최댓값을 사용하였습니다. (INT32_MAX)
 */

class HashTableADT {
public:
    int *table;
    int length;
    HashTableADT(int _length = 1000){ // constructor로 기본 길이는 지정하지 않을시 1000
        length = _length;
        table = new int[length]; // 기본 길이 1000만큼의 배열을 생성
        for(int i=0; i<length; i++)
            table[i] = INT32_MAX; // 기본 값은 전부 int가 가질 수 있는 최댓값을 가지며 비어있는 것을 나타내기 위함
    }
    void put(string, int); // key로 string를, value로 int를 넘겨주고 해쉬함수를 거쳐 hash table 배열의 알맞은 위치에 value를 할당(~O(1))
    int get(string); // string 타입의 key를 넘겨주면 해쉬함수를 거쳐 저장되어있는 value를 리턴(~O(1))
    bool containsKey(string); // key를 넘겨주면 해쉬함수를 거쳐 나온 인덱스에 value가 있는지 판단하여 true 또는 false를 리턴(~O(1))
    bool contains(int); // 파라미터의 정수에 해당하는 value를 리스트가 가지고 있는지 판단하는 함수, 선형탐색(~O(N))
    void remove(string); // 파라미터로 주어진 key의 해쉬함수의 결과가 특정 배열의 인덱스가 될 수 있으면 해당 배열안의 값을 제거(~O(1))
    int hashFunc(string); // 넘겨받은 파라미터를 이용하여 배열의 특정 인덱스가 될 정수를 계산법을 거친 후 리턴해주는 해쉬함수(~O(1))
};

void HashTableADT::put(string key, int value) {
    table[hashFunc(key)] = value; // table의 인덱스로 hashFunc 함수를 불러서 구한 결과값을 사용해 접근 후 value로 값을 덮어씌움
};

int HashTableADT::get(string key) {
    int result = table[hashFunc(key)]; // table의 인덱스로 hashFunc 함수를 불러서 구한 인덱스를 사용하여 안의 값을 구함
    if(result == INT32_MAX) { // 비어있는 경우
        cout << "해당 key를 가진 결과 값이 없습니다." << endl;
        exit(EXIT_FAILURE);
    }
    else { // 비어있지 않은 경우
        return result; // 값을 리턴
    }
};

bool HashTableADT::containsKey(string key) {
    /* table의 index로 hashFunc를 불러 얻은 리턴값을 넣어 값을 조회했을때,
    * 초기 INT32_MAX로 비어있는 경우 true를 그렇지 않으면 false를 리턴 */
    return table[hashFunc(key)] != INT32_MAX;
};

bool HashTableADT::contains(int value) { // 선형탐색하여 value값이 있는지 없는지 조사
    bool found = false; // 결과 플래그로, 초기에는 없는 것으로 가정
    for(int i=0; i<length; i++) // length만큼 반복하여
        if(table[i] == value) // table[i]와 value가 동일한 경우가 존재하면
            found = true; // 결과 플래그를 true로 변경
    return found; // 결과를 리턴
};

void HashTableADT::remove(string key) {
    int resultIndex = hashFunc(key); // table의 인덱스로 hashFunc 함수를 불러서 구한 인덱스를 사용하여 안의 값을 구함
    if(table[resultIndex] == INT32_MAX) { // 비어있는 경우
        cout << "해당 key에는 value가 존재하지 않아 삭제할 수 없습니다." << endl;
    }
    else { // 비어있지 않은 경우
        table[resultIndex] = INT32_MAX; // table의 인덱스로 hashFunc 함수를 구한 인덱스를 사용하여 안의 값을 비어있는 것으로 나타냄
    }

};

int HashTableADT::hashFunc(string key) { // string의 각 자리가 홀수번째에 나오는지 짝수번째에 나오는지에 따라 계산법을 달리 함
    int resultIndex = 0;
    for(int i=0; i<key.length(); i++) {
        if(i%2==0) { // 짝수번째 글자일 경우
            resultIndex+=key[i]; // 그대로 더함
        }
        else { // 홀수번째 글자일 경우
            int tmp = key[i]; // 임시로 char의 ascii값 저장
            int lastDigit;
            int secondLastDigit;
            int ThirdLastDigit;
            if(tmp >= 100) { // ascii 코드상 알파벳 'd' 또는 그 이후로 세자리의 ascii 코드를 가지는 경우
                lastDigit = tmp%10; // 103이라고 가정하면 3이 됨
                tmp/=10; // 103이었다고 가정하면 10이 됨
                secondLastDigit = tmp%10; // 10이었다고 가정하면 0이 됨
                ThirdLastDigit = tmp/10; // 10이었다고 가정하면 1이 됨
                resultIndex+=(lastDigit*100)+(secondLastDigit*10)+ThirdLastDigit; // 103를 뒤집은 301이 된 것을 더해줌
            }
            else { // ascii code상 알파벳 'd' 이전으로 두자리의 ascii 코드를 가지는 경우
                lastDigit = tmp%10; // 75라고 가정하면 5가 됨
                secondLastDigit = tmp/10; // 75라고 가정하면 7이 됨
                resultIndex+=(lastDigit*10)+secondLastDigit; // 75를 뒤집은 57이 된 것을 더해줌
            }
        }
    }
    return resultIndex % length; // 더한값을 리턴해주지만 hash table의 길이를 초과하면 나머지 리턴
}



int main() {
    HashTableADT ht; // HashTable 생성
//    ht.get("Son"); // 아무것도 없는 상태에서 key를 조회하는 경우
    cout << "키 Apple을 가지고 있나?: " << boolalpha << ht.containsKey("Apple") << endl; // 아무 것도 없는 상태에서 key의 조회 여부를 알기위한 함수로 false를 리턴
    cout << "값 23을 가지고 있나?: " << boolalpha << ht.contains(23) << endl; // 아무 것도 없는 상태에서 value를 가지는지를 알기 위한 함수로 false를 리턴
    cout << "키 Apple을 삭제?: "; ht.remove("Apple"); // 해당 hash 함수에 어떠한 값도 가지지 않는 상태에서 key를 remove하려는 경우

    ht.put("Son", 7); // Son에 7을 넣음
    ht.put("Lee", 18); // Lee에 18을 넣음

    ht.put("Kim", 4); // Kim에 4를 넣음
    ht.put("Kim", 19); // Kim에 19를 넣어서 기존 4를 덮어씌움

    ht.put("Hwang", 16); // Hwang에 16을 넣음
    ht.put("Hwang", 11); // Hwang에 11을 넣음

    cout << "key:Son에 해당하는 value는?: " << ht.get("Son") << endl; // Son의 value인 7을 받아옴
    cout << "key:Kim에 해당하는 value는?: " << ht.get("Kim") << endl; // Kim의 처음의 값인 4가 아닌 덮어씌워진 value인 19를 받아옴

    cout << "key:Lee를 가지고 있는가?: " << boolalpha << ht.containsKey("Lee") << endl; // Lee는 존재하므로 참
    cout << "value:11을 가지고 있는가?: " << boolalpha << ht.contains(11) << endl; // 11은 존재하므로 참

    ht.remove("Kim"); // Kim의 키에 대해 삭제
    cout << "key:Kim를 가지고 있는가?: " << ht.containsKey("Kim") << endl; // Kim을 삭제했으므로 false
    return 0;
}

