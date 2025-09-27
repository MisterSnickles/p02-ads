template <class T>
class Grid {
public:
    Grid(int m, int n);
    Grid(int m, int n, T** grid);
    ~Grid();
    int row();
    int col();
    Error_code get(int m, int n, T& result);
    Error_code set(int m, int n, const T& value);
    Error_code setGrid(int m, int n, T** grid);

private:
    int nRow, nCol;
    T** matrix;
};

template <class T>
Grid<T>::Grid(int m, int n) {
    nRow= m;
    nCol = n;
    matrix = new T*[m];
    for (int i = 0; i < m; i++) {
        matrix[i] = new T[n];
    }
}

template <class T>
Grid<T>::Grid(int m, int n, T** grid) {
    nRow= m;
    nCol = n;
    matrix = new T*[m];
    for (int i = 0; i < m; i++) {
        matrix[i] = new T[n];
    }
    setGrid(m, n, grid);
 }

template <class T>
Grid<T>::~Grid() {
    for (int i = 0; i < nRow; i++) {
        delete[] matrix[i];
        matrix[i] = nullptr;
    }
    delete[] matrix;
    matrix = nullptr;
 }

template <class T>
int Grid<T>::row() {
    return nRow;
}

template <class T>
int Grid<T>::col() {
    return nCol;
}

/*
    Get the value at row m, col n.
*/
template <class T>
Error_code Grid<T>::get(int m, int n, T& result) {
    if (m < 0 || m >= nRow || n < 0 || n >= nCol) {
        return range_err;
    }
    result = matrix[m][n];

    return success;
}

/*
    Set the value at row m, col n.
*/
template <class T>
Error_code Grid<T>::set(int m, int n, const T& value) {
    if (m < 0 || m >= nRow || n < 0 || n >= nCol) {
        return range_err;
    }
    matrix[m][n] = value;

    return success;
}

/*
    Copy the input grid into the internal 2D array grid.
*/
template <class T>
Error_code Grid<T>::setGrid(int m, int n, T** grid) {
    if (m > nRow || n > nCol) {
        return range_err;
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = grid[i][j];
        }
    }
    
    return success;
}
