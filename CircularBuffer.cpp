#include <iostream>
#include "CircularBuffer.hpp"

#define mod(a, b) (((a) < 0) ? ((a) % (b) + (b)) : ((a) % (b)))

///////////////////////
////CLASS FUNCTIONS////
///////////////////////


CircularBuffer::CircularBuffer() {
    cap = siz = begin = 0;
    buffer = NULL;
}
CircularBuffer::~CircularBuffer() {

}
CircularBuffer::CircularBuffer(const CircularBuffer & cb) {
    buffer = (value_type*)malloc(cb.cap * sizeof(value_type));
    begin = cb.begin;
    cap = cb.cap;
    siz = cb.siz;
    for (int i = 0; i < cb.siz; i++) {
        buffer[mod(begin + i, cap)] = cb.buffer[mod(begin + i, cap)];
    }
}
CircularBuffer::CircularBuffer(int capacity) {
    buffer = (value_type*)malloc(capacity * sizeof(value_type));
    siz = begin = 0;
    cap = capacity;
}
CircularBuffer::CircularBuffer(int capacity, const value_type & elem) {
    buffer = (value_type*)malloc(capacity * sizeof(value_type));
    for (int i = 0; i < capacity; i++) {
        buffer[i] = elem;
    }
    begin = 0;
    siz = cap = capacity;
}


value_type & CircularBuffer::operator[](int i) {
    return buffer[mod(begin + i, cap)];
}
const value_type & CircularBuffer::operator[](int i) const {
    return buffer[mod(begin + i, cap)];
}
value_type & CircularBuffer::at(int i) {
    try {
        if (i < 0 || i >= siz) {
            throw std::out_of_range("Index error!");
        }
        else {
            return buffer[mod(begin + i, cap)];
        }
    }
    catch (const std::out_of_range& ex) {
        std::cerr << ex.what() << std::endl;
        std::cout << ex.what() << std::endl;
        exit(1);
    }
}
const value_type & CircularBuffer::at(int i) const {
    try {
        if (i < 0 || i >= siz) {
            throw std::out_of_range("Index error!");
        }
        else {
            return buffer[mod(begin + i, cap)];
        }
    }
    catch (const std::out_of_range& ex) {
        std::cerr << ex.what() << std::endl;
        std::cout << ex.what() << std::endl;
        exit(1);
    }
}


value_type & CircularBuffer::front() {
    try {
        if (siz == 0) {
            throw std::range_error("Buffer is empty!");
        }
        else {
            return buffer[begin];
        }
    }
    catch (const std::range_error& ex) {
        std::cerr << ex.what() << std::endl;
        std::cout << ex.what() << std::endl;
        exit(1);
    }
}
value_type & CircularBuffer::back() {
    try {
        if (siz == 0) {
            throw std::range_error("Buffer is empty!");
        }
        else {
            return buffer[mod(begin + siz - 1, cap)];
        }
    }
    catch (const std::range_error& ex) {
        std::cerr << ex.what() << std::endl;
        std::cout << ex.what() << std::endl;
        exit(1);
    }
}
const value_type & CircularBuffer::front() const {
    try {
        if (siz == 0) {
            throw std::range_error("Buffer is empty!");
        }
        else {
            return buffer[begin];
        }
    }
    catch (const std::range_error& ex) {
        std::cerr << ex.what() << std::endl;
        std::cout << ex.what() << std::endl;
        exit(1);
    }
}
const value_type & CircularBuffer::back() const {
    try {
        if (siz == 0) {
            throw std::range_error("Buffer is empty!");
        }
        else {
            return buffer[mod(begin + siz - 1, cap)];
        }
    }
    catch (const std::range_error& ex) {
        std::cerr << ex.what() << std::endl;
        std::cout << ex.what() << std::endl;
        exit(1);
    }
}


value_type * CircularBuffer::linearize() {
    value_type* store = (value_type*)malloc(siz * sizeof(value_type));
    int cnt = siz;
    for (int i = 0; i < siz; i++) {
        store[i] = this->back();
        this->pop_back();
    }
    begin = 0;
    for (int i = cnt - 1; i >= 0; i--) {
        this->push_back(store[i]);
    }
    free(store);
    return buffer;
}
bool CircularBuffer::is_linearized() const {
    return begin == 0;
}
void CircularBuffer::rotate(int new_begin) {
    try {
        if (new_begin < 0 || new_begin >= siz) {
            throw std::out_of_range("Index error!");
        }
        else {
            int cnt = siz;
            value_type* store = (value_type*)malloc(cnt * sizeof(value_type));
            for (int i = 0; i < siz; i++) {
                store[i] = this->back();
                this->pop_back();
            }
            begin += new_begin;
            for (int i = cnt - 1; i >= 0; i--) {
                this->push_back(store[i]);
            }
            free(store);
        }
    }
    catch (const std::out_of_range& ex) {
        std::cerr << ex.what() << std::endl;
        std::cout << ex.what() << std::endl;
        exit(1);
    }
}
int CircularBuffer::size() const {
    return siz;
}
bool CircularBuffer::empty() const {
    return siz == 0;
}
bool CircularBuffer::full() const {
    return siz == cap;
}
int CircularBuffer::reserve() const {
    return cap - siz;
}
int CircularBuffer::capacity() const {
    return cap;
}


void CircularBuffer::set_capacity(int new_capacity) {
    if (new_capacity != cap && new_capacity > 0) {
        value_type* store = NULL;
        int cnt = begin + siz - cap;
        if (cnt > 0) {                                                  // На случай элементов между 0 истинным и begin
            store = (value_type*)malloc(cnt * sizeof(value_type));
            for (int i = 0; i < cnt; i++) {
                store[i] = this->back();
                this->pop_back();
            }
        }
        if (new_capacity > cap) {                                       // Если буфер расширяют
            buffer = (value_type*)realloc(buffer, new_capacity * sizeof(value_type));
            cap = new_capacity;
            for (int i = cnt - 1; i >= 0; i--) {
                this->push_back(store[i]);
            }
        }
        else {                                                          // Если буфер уменьшают
            int diff = cap - new_capacity;
            if (cnt >= 0) {                                             // Если есть элементы между 0 истинным и begin
                store = (value_type*)realloc(store, (cnt + diff) * sizeof(value_type));
                for (int i = 0; i < diff; i++) {
                    store[cnt + i] = this->back();
                    this->pop_back();
                }
                cap = new_capacity;
                int i = cnt + diff -1;
                while (siz < cap && i >= 0) {
                    this->push_back(store[i]);
                }
            }
            else {                                                      // Если нет элементов между 0 истинным и begin
                if (-cnt >= diff) {                                     // Если свободное место в буфере позволяет его уменьшить без переноса элементов
                    buffer = (value_type*)realloc(buffer, new_capacity * sizeof(value_type));
                    cap = new_capacity;
                }
                else {                                                  // Если свободное место в буфере не позволяет его уменьшить без переноса элементов
                    cnt = diff + cnt;
                    store = (value_type*)malloc(cnt * sizeof(value_type));
                    for (int i = 0; i < cnt; i++) {
                        store[i] = this->back();
                        this->pop_back();
                    }
                    buffer = (value_type*)realloc(buffer, new_capacity * sizeof(value_type));
                    cap = new_capacity;
                    int i = cnt - 1;
                    while (siz < cap && i >= 0) {
                        this->push_back(store[i]);
                    }
                }
            }
        }
        free(store);
    }
    else if (new_capacity == 0) {
        free(buffer);
        *this = CircularBuffer();
    }
}
void CircularBuffer::resize(int new_size, const value_type & item) {
    if (new_size != siz && new_size >= 0) {
        if (new_size > siz) {
            value_type* store = NULL;
            int cnt = begin + siz - cap;
            if (cnt > 0) {
                store = (value_type*)malloc(cnt * sizeof(value_type));
                for (int i = 0; i < cnt; i++) {
                    store[i] = this->back();
                    this->pop_back();
                }
            }
            if (new_size > cap) {
                buffer = (value_type*)realloc(buffer, new_size * sizeof(value_type));
                cap = new_size;
            }
            if (store) {
                for (int i = cnt - 1; i >=0; i--) {
                    this->push_back(store[i]);
                }
                free(store);
            }
            for (int i = siz; i < new_size; i++) {
                this->push_back(item);
            }
        }
        else {
            siz = new_size;
        }
    }
}
CircularBuffer & CircularBuffer::operator=(const CircularBuffer & cb) {
    free(buffer);
    buffer = NULL;
    *this = CircularBuffer(cb);
    return *this;
}
void CircularBuffer::swap(CircularBuffer & cb) {
    CircularBuffer temp(cb);
    cb = *this;
    *this = temp;
}


void CircularBuffer::push_back(const value_type & item) {
    buffer[mod(begin + siz, cap)] = item;
    if (mod(begin + siz, cap) == begin) {
        begin++;
        siz--;
    }
    siz++;
}
void CircularBuffer::push_front(const value_type & item) {
    begin = mod(begin - 1, cap);
    buffer[begin] = item;
    if (siz != cap) siz++;
}
void CircularBuffer::pop_back() {
    if (siz != 0) {
        buffer[mod(begin + siz - 1, cap)] = 66;
        siz--;
    }
}
void CircularBuffer::pop_front() {
    if (siz != 0) {
        buffer[begin] = 66;
        begin = mod(begin + 1, cap);
        siz--;
    }
}


void CircularBuffer::insert(int pos, const value_type & item) {
    try {
        if (pos < 0 || pos >= siz) {
            throw std::out_of_range("Index is out of range!");
        }
        else {
            int cnt = siz - pos;
            value_type* store = (value_type*)malloc(cnt * sizeof(value_type));
            for (int i = 0; i < cnt; i++) {
                store[i] = this->back();
                this->pop_back();
            }
            this->push_back(item);
            for (int i = cnt - 1; i > 0; i--) {
                this->push_back(store[i]);
            }
            free(store);
        }
    }
    catch (const std::out_of_range& ex) {
        std::cerr << ex.what() << std::endl;
        std::cout << ex.what() << std::endl;
        exit(1);
    }
}
void CircularBuffer::erase(int first, int last) {
    try {
        if (first < 0 || first >= siz || last < 0 || last >= siz || first > last) {
            throw std::range_error("Indexes are out of range!");
        }
        else {
            int cnt = siz - last + 1;
            value_type* store = (value_type*)malloc(cnt * sizeof(value_type));
            for (int i = 0; i < cnt; i++) {
                store[i] = this->back();
                this->pop_back();
            }
            for (int i = first; i < last; i++) this->pop_back();
            for (int i = cnt - 1; i >= 0; i--) {
                this->push_back(store[i]);
            }
            free(store);
        }
    }
    catch (const std::range_error& ex) {
        std::cerr << ex.what() << std::endl;
        std::cout << ex.what() << std::endl;
        exit(1);
    }
}
void CircularBuffer::clear() {
    free(buffer);
    buffer = (value_type*)malloc(cap * sizeof(value_type));
    siz = 0;
    
    //*this = CircularBuffer();
}

////////////////////////
////COMMON FUNCTIONS////
////////////////////////

bool operator==(const CircularBuffer & a, const CircularBuffer & b) {
    if (a.size() != b.size() || a.capacity() != b.capacity()) return false;
    int siz = a.size();
    for (int i = 0; i < siz; i++) {
        if (a[i] != b[i]) return false;    
    }
    return true;
}
bool operator!=(const CircularBuffer & a, const CircularBuffer & b) {
    return !(a == b);
}
