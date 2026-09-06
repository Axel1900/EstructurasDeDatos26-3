#pragma once
#include <string>
#include <iostream>
#include "ConsoleUI.h"

// =====================================================================
//  HashTable<V>  -  Tabla asociativa (llave string, valor generico)
//
//  Las llaves SIEMPRE son std::string. El valor es lo que sea (V).
//
//  COMO FUNCIONA:
//  Una tabla hash convierte la llave en un NUMERO (el hash), y usa ese
//  numero como indice del arreglo de buckets. Por eso buscar es O(1)
//  en promedio: no recorre nada, calcula directo donde deberia estar.
//
//  COLISIONES: dos llaves distintas pueden dar el mismo hash. Cuando
//  pasa, ambas tienen que caber en el mismo bucket. La solucion que
//  vas a implementar se llama ENCADENAMIENTO: cada bucket no guarda
//  una entrada, guarda una lista ligada de entradas.
// =====================================================================

template <class V>
class HashTable
{
private:
    struct Entry
    {
        std::string key;
        V value;
        Entry* next;
    };

    Entry** _buckets;
    int _capacidad;
    int _size;

public:
    HashTable(int capacidad);
    ~HashTable();

    int Hash(std::string key);
    void Insert(std::string key, V value);
    V Get(std::string key);
    bool Contains(std::string key);
    bool Remove(std::string key);
    int GetSize();
    int GetCapacidad();
    void Print();
};

template <class V>
HashTable<V>::HashTable(int capacidad)
{
    // Arrancan en nullptr para que nada truene antes de reservar.
    // NO borres estas lineas.
    _buckets = nullptr;
    _capacidad = capacidad;
    _size = 0;

    _buckets = new Entry*[_capacidad];

    for (int i = 0; i < _capacidad; i++)
    {
        _buckets[i] = nullptr;
    }
}

template <class V>
HashTable<V>::~HashTable()
{
    for (int i = 0; i < _capacidad; i++)
    {
        Entry* actual = _buckets[i];
        while (actual != nullptr)
        {
            Entry* siguiente = actual->next;
            delete actual; 
            actual = siguiente;
        }
    }

    delete[] _buckets;
}

template <class V>
int HashTable<V>::Hash(std::string key)
{

    unsigned long long hash = 0; 
    for (unsigned int i = 0; i < key.length(); i++)
    {
        hash = hash * 31 + key[i]; 
    }

    return (int)(hash % (unsigned long long)_capacidad);
}

template <class V>
void HashTable<V>::Insert(std::string key, V value)
{
    int bucket = Hash(key);

    Entry* actual = _buckets[bucket];
    while (actual != nullptr)
    {
        if (actual->key == key)
        {
            actual->value = value;
            return;
        }
        actual = actual->next;
    }

    Entry* nuevo = new Entry();
    nuevo->key = key;
    nuevo->value = value;
    nuevo->next = _buckets[bucket];
    _buckets[bucket] = nuevo;
    _size++; 
}

template <class V>
V HashTable<V>::Get(std::string key)
{
    int bucket = Hash(key);
    Entry* actual = _buckets[bucket];
    while (actual != nullptr)
    {
        if (actual->key == key)
        {
            return actual->value;
        }
        actual = actual->next;
    }

    ConsoleUI::PrintError("HashTable: la llave no existe: " + key);
    return V();
}

template <class V>
bool HashTable<V>::Contains(std::string key)
{
    int bucket = Hash(key);
    Entry* actual = _buckets[bucket];
    while (actual != nullptr)
    {
        if (actual->key == key)
            return true;
        actual = actual->next;
    }
    return false;
}

template <class V>
bool HashTable<V>::Remove(std::string key)
{
    int bucket = Hash(key);
    Entry* actual = _buckets[bucket];
    Entry* anterior = nullptr;

    while (actual != nullptr)
    {
        if (actual->key == key)
        {

            if (anterior == nullptr)
            {
                _buckets[bucket] = actual->next;
            }
            else
            {
                anterior->next = actual->next;
            }

            _size--;
            delete actual;
            return true;  
        }

        anterior = actual;
        actual = actual->next; 
    }

    return false;
}

template <class V>
int HashTable<V>::GetSize()
{
    return _size;
}

template <class V>
int HashTable<V>::GetCapacidad()
{
    return _capacidad;
}

template <class V>
void HashTable<V>::Print()
{
    for (int i = 0; i < _capacidad; i++)
    {
        std::cout << "Bucket " << i << ": ";
        Entry* actual = _buckets[i];
        while (actual != nullptr)
        {
            std::cout << "[" << actual->key << "=" << actual->value << "] -> ";
            actual = actual->next;
        }
        std::cout << "(fin)" << std::endl;
    }
}
