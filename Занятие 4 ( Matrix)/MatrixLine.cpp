#include "MatrixLine.h"

Matrix::Matrix(int rowC, int columnC, t** array) {
    columns = columnC;
    rows = rowC;

    if (rowC == 0 || columnC == 0) {
        return;
    }
    
    IndexAr = new t*[rowC];
    unsigned int size = rowC * columnC;
    setBuf(size);
    
    for (int i = 0; i < rowC; i++) {
        IndexAr[i] = &buf[i * columnC];
    }    
    if (array != nullptr) {
        for (int i = 0; i < rowC; i++)
            for (int j = 0; j < columnC; j++)
                (*this)[i][j] = array[i][j];
    }
}

Matrix::Matrix(int rowC, int columnC, t* array) {
    columns = columnC;
    rows = rowC;

    if (rowC == 0 || columnC == 0) {
        IndexAr = nullptr;
        buf = nullptr;
        return;
    }

    IndexAr = new t*[rowC];
    unsigned int size = rowC * columnC;
    setBuf(size);

    for ( int i = 0; i < rowC; i++) {
        IndexAr[i] = &buf[i * columnC];
    }
    if (array != nullptr) {
        for (int i = 0; i < rowC; i++)
            for (int j = 0; j < columnC; j++)
                (*this)[i][j] = array[i * columns + j];
    }
}

void Matrix::setMatrix(int rowC, int columnC, t* array) {
    columns = columnC;
    rows = rowC;

    if (rowC == 0 || columnC == 0) {
        IndexAr = nullptr;
        buf = nullptr;
        return;
    }

    IndexAr = new t*[rowC];
    unsigned int size = rowC * columnC;
    setBuf(size);

    for (int i = 0; i < rowC; i++) {
        IndexAr[i] = &buf[i * columnC];
    }
    if (array != nullptr) {
        for (int i = 0; i < rowC; i++)
            for (int j = 0; j < columnC; j++)
                (*this)[i][j] = array[i * columns + j];
    }
}

Matrix:: ~Matrix() {
    delete[] IndexAr;
    delete[] buf;
}


void Matrix::setBuf(unsigned int size) {
    buf = new t[size];
}

Matrix::t* Matrix:: operator [](unsigned int index) {
    if (index <= rows)
        return IndexAr[index];
    else
        assert(true);
}

Matrix::t* Matrix:: operator [](unsigned int index) const {
    if (index <= rows)
        return IndexAr[index];
    else
        assert(true);
}

Matrix Matrix:: operator * (const Matrix& m2) const {    
    if (columns == m2.rows) {
        Matrix m(rows, m2. columns);
        for (unsigned int i = 0; i < rows; i++)
            for (unsigned int j = 0; j < m2.columns; j++) {
                t sum = 0;
                for (unsigned int b = 0; b < columns; b++) {
                    sum += (*this)[i][b] * m2[b][j];
                }
                m[i][j] = sum;
            }       
        return m;
    }
    else
        assert(true);
}

Matrix Matrix:: operator + (const Matrix& m2) const {
    if (rows == m2.rows && columns == m2.columns) {
        Matrix m(rows, columns);
        for (unsigned int i = 0; i < rows; i++)
            for (unsigned int j = 0; j < columns; j++)
                m[i][j] = (*this)[i][j] + m2[i][j];
        return m;
    }
    else
        assert(true);
}

Matrix Matrix:: operator * (const Matrix::t k) const {
    Matrix m(rows, columns);
    for (unsigned int i = 0; i < rows; i++) {
        for (unsigned int j = 0; j < columns; j++)
            m[i][j] = (*this)[i][j] * k;
    }
    return m;
}

Matrix operator * (const Matrix::t k, const Matrix& m2) {
    Matrix m(m2.rows,m2.columns);
    for (unsigned int i = 0; i < m2.rows; i++)
        for (unsigned int j = 0; j < m2.columns; j++)
            m[i][j] = m2[i][j] * k;
    return m;
}

Matrix::Matrix(const Matrix& m2) {
    columns = m2.columns;
    rows = m2.rows;

    if (m2.rows == 0 || m2.columns == 0) {
        IndexAr = nullptr;
        buf = nullptr;
        return;
    }

    IndexAr = new t*[m2.rows];
    unsigned int size = m2.rows * m2.columns;
    setBuf(size);

    for (unsigned int i = 0; i < m2.rows; i++) {
        IndexAr[i] = &buf[i * m2.columns];
    }

    for (unsigned int i = 0; i < m2.rows; i++)
        for (unsigned int j = 0; j < m2.columns; j++)
            (*this)[i][j] = m2[i][j];
}


void Matrix:: setMatrix(int rows, int columns, t** array) {
    this->clear();
    Matrix(rows, columns, array);
}

Matrix& Matrix:: operator = (const Matrix& m2) {
    clear();
    columns = m2.columns;
    rows = m2.rows;

    if (m2.rows == 0 || m2.columns == 0) {
        IndexAr = nullptr;
        buf = nullptr;
        return *this;
    }

    IndexAr = new t*[m2.rows];
    unsigned int size = m2.rows * m2.columns;
    setBuf(m2.rows * m2.columns);

    for (unsigned int i = 0; i < m2.rows; i++) {
        IndexAr[i] = &buf[i * m2.columns];
    }

    for (int i = 0; i < m2.rows; i++)
        for (int j = 0; j < m2.columns; j++)
            (*this)[i][j] = m2[i][j];
    return *this;
}

void Matrix::clear() {
    delete[] buf;
    delete[] IndexAr;
    rows = 0;
    columns = 0;
}

Matrix& Matrix:: operator *= (const Matrix& m2) {
    *this = (*this) * m2;
    return *this;
}

Matrix& Matrix:: operator += (const Matrix& m2) {
    *this = (*this) + m2;
    return *this;
}

Matrix& Matrix:: operator *= (const Matrix::t k) {
    *this = (*this) * k;
    return *this;
}

Matrix& Matrix:: transp() {
    t* tempbuf = new t[rows * columns];
    for (int i = 0; i < columns; i++)
        for (int j = 0; j < rows; j++)
            tempbuf[i * columns + j] = (*this)[i][j];
    int temprows = rows;
    int tempcol = columns;
    clear();
    setMatrix(tempcol, temprows, tempbuf);
    return *this;
}

squareMatrix:: squareMatrix(int rowC, int columnC, t** array) {
    if (rowC == columnC) {
        columns = columnC;
        rows = rowC;

        if (rowC == 0 || columnC == 0) {
            IndexAr = nullptr;
            buf = nullptr;
            return;
        }

        IndexAr = new t*[rowC];
        unsigned int size = rowC * columnC;
        setBuf(rowC * columnC);

        for (unsigned int i = 0; i < rowC; i++) {
            IndexAr[i] = &buf[i * columnC];
        }
        if (array != nullptr) {
            for (int i = 0; i < rowC; i++)
                for (int j = 0; j < columnC; j++)
                    (*this)[i][j] = array[i][j];
        }
    }
    else
        assert(true);
}

squareMatrix::squareMatrix(int rowC, int columnC, t* array) {
    if (rowC == columns) {
        columns = columnC;
        rows = rowC;

        if (rowC == 0 || columnC == 0) {
            IndexAr = nullptr;
            buf = nullptr;
            return;
        }

        IndexAr = new t*[rowC];
        unsigned int size = rowC * columnC;
        setBuf(rowC * columnC);

        for (unsigned int i = 0; i < rowC; i++) {
            IndexAr[i] = &buf[i * columnC];
        }
        
        for (int i = 0; i < rowC; i++)
            for (int j = 0; j < columnC; j++)
                (*this)[i][j] = array[i * columns + j];
    }
    else
        assert(true);
}

squareMatrix:: ~squareMatrix() {
}
int Matrix:: getrows()const {
    return rows;
}
int Matrix::getcolumns()const {
    return columns;
}

squareMatrix::squareMatrix(const Matrix& m2) {
    if (m2.getrows() == m2.getcolumns())
        Matrix(m2);
    else
        assert(true);
}

std::ostream& operator <<(std::ostream& output, Matrix& s) {
    for (unsigned int i = 0; i < s.rows; i++) {
        for (unsigned int j = 0; j < s.columns; j++)
            output << s[i][j] << ' ';
        output << std::endl;
    }
    return output;
}


std::istream& operator >>(std::istream& in, Matrix& s) {
    unsigned int row, column;
    in >> row;
    in >> column;
    Matrix::t a;
    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++) {
            in >> a;
            s[i][j] = a;
        }
    return in;
}

Matrix::t& squareMatrix:: operator = (const squareMatrix) {
    if (rows == columns && rows == 1)
        return (*this)[0][0];
    else
        assert(true);
}

double squareMatrix::Determinant() {
    // Gauss method, a two-dimensional array because we should always have double
    if (rows == columns) {
        int n = rows;
        if (n == 1)
            return (*this)[0][0];
        if (n == 2)
            return (*this)[0][0] * (*this)[1][1] - (*this)[0][1] * (*this)[1][0];

        double** temp = new double*[n];
        for (int i = 0; i < n; i++)
           temp[i] = new double[n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                temp[i][j] = (*this)[i][j];

        double kst;
        int p = 0;
        for (int i = 0; i < n - 1; i++)
        {
            int t = 1;
            while (temp[i][i] == 0)
            {
                for (int j = 0; j<n; j++)
                {
                    temp[i][j] = kst;
                    temp[i][j] = temp[i + t][j];
                    temp[i + t][j] = kst;
                }
                p++;
                t++;
            }

            for (int k = i + 1; k<n; k++)
            {
                kst = temp[k][i] / temp[i][i];
                for (int j = 0; j<n; j++)
                    temp[k][j] -= temp[i][j] * kst;
            }
        }

        kst = pow(-1, p);
        for (int i = 0; i<n; i++)
            kst *= temp[i][i];



        for (int i = 0; i < n; i++)
            delete[] temp[i];
        delete[] temp;

        return kst;
    }
    else
        assert(true);
}