#include "SuffArray.h"

/*
    ¬ыполн€ем пор€дка log(S) итераций, в каждой из которых сортируем циклические сдвиги длины 1,2,4,8...
    ѕерва€ итераци€ сортирует сдвиги по первому элементу подсчетом, затем кажда€ итераци€ получает на вход массив,
    отсортированный по первым I символам циклических сдвигов, а также массив классов эквивалентности такой что:
    ќн отсортирован по возрастанию относительно символо циклических сдвигов, и одинаковые по первым I символам
    циклические сдвиги в одном классе эквивалентности, иначе в разных. ¬сего классов |S|.
    Ќа каждой итерации вычисл€ютс€ аналогичные массивы, дл€ в два раза большего количества символов в сдвиге.
    «аметим, что кажда€ нова€ подстрока длины 2l - конкатенаци€ 2х уже посчитанных длины l.
    «начит, така€ подстрока S[i..(i+2l-1)%|S|] может быть представлена в виде пары чисел
    classes[i],classes[(i+l)%|S|] и достаточно отсортировать только эти пары.
    ѕользуемс€ методом BucketSort. —ортируем устойчивым подсчетом сначала по 2му числу потом по 1му
    (сортировка по второму была выполнена на предыдущей терации).
*/
void CSuffArray::sortingCycleShifts( vector<int>& answer ) {
    int size = st.size();
    answer.assign( size, 0 );
    vector<int> newPermutation( size ), classes( size ), newClasses( size ), h( size );
    int alphSize = 256;

    h.assign( alphSize, 0 );
    for( int i = 0; i < size; ++i ) {
        classes[i] = st[i];
        h[st[i]]++;
    }
    for( int i = 1; i < h.size(); ++i ) {
        h[i] += h[i - 1];
    }
    for( int i = size - 1; i >= 0; --i ) {
        newPermutation[--h[classes[i]]] = i;
    }

    answer.swap( newPermutation );

    for( int l = 1; l <= size; l += l ) {
        h.assign( alphSize, 0 );
        for( int j = 0; j < size; ++j ) {
            h[classes[j]]++;
        }
        for( int j = 1; j < alphSize; ++j ) {
            h[j] += h[j - 1];
        }
        for( int i = size - 1; i >= 0; --i ) {
            int v = ( answer[i] - l + size ) % size;
            newPermutation[--h[classes[v]]] = v;
        }
        answer.swap( newPermutation );
        alphSize = 1;
        newClasses[answer[0]] = 0;
        for( int i = 1; i < size; ++i ) {
            if( ( classes[answer[i]] == classes[answer[i - 1]] ) && ( classes[( answer[i] + l ) % size] == classes[( answer[i - 1] + l ) % size] ) ) {
                newClasses[answer[i]] = alphSize - 1;
            }
            else {
                newClasses[answer[i]] = alphSize++;
            }
        }
        classes.swap( newClasses );
    }
    return;
};

/* «аметим, что сравнение i и j суффиксов строки, равносильно сравнению i и j левых циклических сдвигов строки S$.
   ќписание сортировки циклических сдвигов находитс€ над соответствующим методом.
*/
void CSuffArray::createSuffArray() {
    const_cast< string& > ( st ) += '$';
    sortingCycleShifts( SuffArray );
    SuffArray.erase( SuffArray.begin() );
    const_cast< string& > ( st ).pop_back();
};

vector<int> CSuffArray::buildLCP( const string& str, const vector<int>& suffArr ) {
    int len = str.length();
    vector<int> lcp( len );
    // ћассив обратный массиву суффиксов.
    vector<int> convSuff( len );
    for( int i = 0; i < len; ++i ) {
        convSuff[suffArr[i]] = i;
    }
    int k = 0;
    for( int i = 0; i < len; ++i ) {
        if( k > 0 ) {
            k--;
        }
        if( convSuff[i] == len - 1 ) {
            lcp[len - 1] = -1;
            k = 0;
        }
        else {
            int j = suffArr[convSuff[i] + 1];
            while( std::max( i + k, j + k ) < len && str[i + k] == str[j + k] ) {
                k++;
            }
            lcp[convSuff[i]] = k;
        }
    }
    return lcp;
}