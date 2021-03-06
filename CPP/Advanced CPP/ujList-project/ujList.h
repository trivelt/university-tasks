/** @mainpage
  * @par Kontener lista jednokierunkowa
  * @a Projekt na zajecia "Zaawansowane techniki programowania obiektowego w C++"
  * @author Maciej Michalec
  * @par Kontakt:
  * @a maciej.michalec@uj.edu.pl
  * @date 27.06.2015
*/

#ifndef UJLIST_H
#define UJLIST_H
#include <iostream>
#include <iterator>

namespace uj {

    template<typename T> class list
    {
    public:
        typedef T value_type;
        typedef value_type& reference;
        typedef const reference const_reference;

        struct element
        {
            T value;
            element* next;

            element(T val);
        };

        struct iterator : std::iterator<std::random_access_iterator_tag, T*>
        {
            element* previous;
            bool isHead;

            iterator();
            iterator(element* ptrToPrevious, bool isHead=false);
            iterator(const iterator& other);
            iterator & operator++();
            iterator & operator++(int);
            bool operator==(iterator other) const;
            bool operator!=(iterator other) const;
            T & operator*();
            T * operator->();
        };

        element* head;
        element* tail;

        list();
        list(const list & other);
        ~list();

        list & operator=(const list & other);
        bool empty() const;
        size_t size() const;

        iterator begin() const;
        iterator end() const;

        void clear();
        iterator insert(iterator pos, const T & value);
        iterator erase(iterator pos);
    };


    template<typename T> list<T>::element::element(T val) : value(val), next(nullptr) {}

    /**
      * @brief Konstruktor bezparametrowy
      *
      * Tworzy nowy iterator, inicjalizujac wskaznik do elementu poprzedniego
      * jako null oraz flage isHead jako false.
      *
      * Zlozonosc czasowa: O(1)
      */
    template<typename T> list<T>::iterator::iterator() : previous(nullptr), isHead(false) {}

    /**
      * @brief Konstruktor
      * @param ptrToPrevious wskaznik do poprzedniego elementu
      * @param isHead flaga - TRUE jesli element jest glowa listy
      *
      * Tworzy nowa iterator.
      *
      * Zlozonosc czasowa: O(1)
      */
    template<typename T> list<T>::iterator::iterator(element *ptrToPrevious, bool isHead)
    {
        this->previous = ptrToPrevious;
        this->isHead = isHead;
    }

    /**
      * @brief Konstruktor kopiujacy
      * @param other referencja do iteratora
      *
      * Tworzy nowa iterator na podstawie innego.
      *
      * Zlozonosc czasowa: O(1)
      */
    template<typename T> list<T>::iterator::iterator(const iterator & other) :
        previous(other.previous),
        isHead(other.isHead) {}

    /**
      * @brief Preinkrementacja
      * @return Referencja do iteratora
      *
      *
      * Zlozonosc czasowa: O(1)
      */
    template<typename T> typename list<T>::iterator & list<T>::iterator::operator++()
    {
        if(isHead)
        {
            isHead = false;
        }
        else
        {
            previous = previous->next;
        }
    }

    /**
      * @brief Postinkrementacja
      * @return Referencja do iteratora
      *
      *
      * Zlozonosc czasowa: O(1)
      */
    template<typename T> typename list<T>::iterator & list<T>::iterator::operator++(int)
    {
        iterator beforeIncrementation(*this);
        if(isHead)
        {
            isHead = false;
        }
        else
        {
            previous = previous->next;
        }
        return beforeIncrementation;
    }

    /**
      * @brief Operator porownania
      * @param other Iterator
      * @return Wartosc logiczna true jesli iteratory sa sobie rowne, wpp false
      *
      *
      * Zlozonosc czasowa: O(1)
      */
    template<typename T> bool list<T>::iterator::operator==(list<T>::iterator other) const
    {
        return (this->previous==other.previous && this->isHead==other.isHead);
    }

    /**
      * @brief Operator porownania
      * @param other Iterator
      * @return Wartosc logiczna true jesli iteratory sa od siebie rozne, wpp false
      *
      *
      * Zlozonosc czasowa: O(1)
      */
    template<typename T> bool list<T>::iterator::operator!=(list<T>::iterator other) const
    {
        return (this->previous != other.previous || this->isHead != other.isHead);
    }

    /**
      * @brief Operator wyluskania
      * @return Referencja do wartosci wskazywanej przez iterator
      *
      * Zlozonosc czasowa: O(1)
      */
    template<typename T> T & list<T>::iterator::operator*()
    {
        if(isHead)
            return previous->value;
        else
            return previous->next->value;
    }

    /**
      * @brief Operator "strzalka"
      * @return Wskaznik do wartosci wskazywanej przez iterator
      *
      * Zlozonosc czasowa: O(1)
      */
    template<typename T> T * list<T>::iterator::operator->()
    {
        if(isHead)
            return &previous->value;
        else
            return &previous->next->value;
    }


    /**
      * @brief Konstruktor bezparametrowy
      *
      * Tworzy nowa liste.
      *
      * Zlozonosc czasowa: O(1)
      */
    template<typename T> list<T>::list() : head(nullptr), tail(nullptr) {}


    /**
      * @brief Konstruktor
      * @param other referencja do listy
      *
      * Tworzy nowa liste na podstawie podanej w argumencie.
      *
      * Zlozonosc czasowa: O(n)
      */
    template<typename T> list<T>::list(const list & other)
    {
        iterator it = other.begin();
        if(other.empty())
        {
            head = nullptr;
            tail = nullptr;
            return;
        }

        element headElement(*it);
        head = &headElement;

        iterator insertedElement = this->begin();
        for(++it; it != other.end(); ++it)
        {
            insertedElement = this->insert(++insertedElement, *it);
        }
        tail = insertedElement.previous->next;
    }

    /**
      * @brief Destruktor
      *
      * Destruktor listy. Usuwa z niej wszystkie elementy.
      *
      * Zlozonosc czasowa: O(n)
      */
    template<typename T> list<T>::~list()
    {
        this->clear();
    }

    /**
      * @brief Operator przypisania
      * @param other referencja do listy
      * @return Referencja do utworzonej listy
      *
      * Tworzy nowa liste na podstawie podanej w argumencie
      *
      * Zlozonosc czasowa: O(n)
      */
    template<typename T> list<T> & list<T>::operator=(const list & other)
    {
        list<T> newList(other);
        return &newList;
    }

    /**
      * @brief Sprawdza czy lista jest pusta
      * @return true jesli lista jest pusta, w przeciwnym wypadku - false
      *
      * Funkcja sprawdzajaca czy lista zawiera niezerowa liczbe elementow.
      *
      * Zlozonosc czasowa: O(1)
      */
    template<typename T> bool list<T>::empty() const
    {
        return (head == nullptr);
    }

    /**
      * @brief Rozmiar listy
      * @return Liczba elementow w liscie
      *
      * Funkcja obliczajaca i zwracajaca rozmiar listy.
      *
      * Zlozonosc czasowa: O(n)
      */
    template<typename T> size_t list<T>::size() const
    {
        size_t counter = 0;
        for(iterator it=this->begin(); it != this->end(); ++it)
        {
            counter++;
        }
        return counter;
    }

    /**
      * @brief Zwraca iterator na poczatek listy
      * @return Iterator na pierwszy element listy
      *
      * Funkcja zwraca iterator wskazujacy na poczatek listy.
      *
      * Zlozonosc czasowa: O(1)
      */
    template<typename T> typename list<T>::iterator list<T>::begin() const
    {
        if(this->empty())
            return iterator(head, false);
        else
            return iterator(head, true);
    }

    /**
      * @brief Iterator poza lista
      * @return Iterator na miejsce za koncem listy
      *
      * Funkcja zwraca iterator wskazujacy na miejsce za koncem listy,
      * czyli wskaznik nullptr.
      *
      * Zlozonosc czasowa: O(1)
      */
    template<typename T> typename list<T>::iterator list<T>::end() const
    {
        return iterator(tail);
    }

    /**
      * @brief Czyszczenie listy
      *
      * Funkcja usuwajaca z listy wszystkie elementy.
      *
      * Zlozonosc czasowa: O(n)
      */
    template<typename T> void list<T>::clear()
    {
        for(iterator it=this->begin(); it != this->end();)
        {
            it = this->erase(it);
        }
    }

    /**
      * @brief Dodawanie nowego elementu
      * @param pos iterator wskazujacy na pozycje nowego elementu
      * @param value wartosc nowego elementu
      * @return Iterator na dodany element
      *
      * Funkcja wstawia nowy element bezposrednio przed elementem
      * wskazywanym przez podany iterator. Zwracanym obiektem jest
      * iterator na nowo utworzony element listy.
      *
      * Zlozonosc czasowa: O(1)
      */
    template<typename T> typename list<T>::iterator list<T>::insert(iterator pos, const T & value)
    {
        element* newElement = new element(value);
        if(pos == this->end())
        {
            tail = newElement;
        }
        if(pos == this->begin())
        {
            // Dodajemy element na poczatek listy
            if(!this->empty())
            {
                element* oldElement = pos.previous;
                newElement->next = oldElement;
            }
            head = newElement;
            return iterator(newElement, true);
        }
        else
        {
            element* previousElement = pos.previous;
            element* oldElement = previousElement->next;
            newElement->next = oldElement;
            previousElement->next = newElement;
            return iterator(previousElement);
        }
    }

    /**
      * @brief Usuwanie elementu z listy
      * @param pos iterator wskazujacy na element do usuniecia
      * @return Iterator na element nastepny po usunietym
      *
      * Funkcja pobiera jako argument iterator do elementu listy
      * i usuwa go z niej. Zwracanym obiektem jest iterator do
      * elementu nastepnego po usunietym.
      *
      * Zlozonosc czasowa: O(1)
      */
    template<typename T> typename list<T>::iterator list<T>::erase(iterator pos)
    {
        element* elementToErase;
        if(pos == this->begin())
        {
            elementToErase = pos.previous;
            if(elementToErase->next == nullptr)
            {
                // Usuwamy HEAD z jednoelementowej listy
                head = nullptr;
                tail = nullptr;

                iterator nextElement(head);
                delete elementToErase;
                return nextElement;
            }
            else
            {
                // Usuwamy HEAD z wieloelementowej listy
                head = elementToErase->next;

                iterator nextElement(elementToErase->next, true);
                delete elementToErase;
                return nextElement;
            }
        }
        else
        {
            // Usuwamy element, ktory nie jest glowa listy
            elementToErase = pos.previous->next;
            element* previousElement = pos.previous;
            previousElement->next = elementToErase->next;
            if(elementToErase->next == nullptr)
            {
                tail = previousElement;
            }
            iterator nextElement(elementToErase);
            delete elementToErase;
            return nextElement;
        }
    }

}

#endif // UJLIST_H
