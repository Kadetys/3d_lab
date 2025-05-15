// 3d_lab1.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "3d_lab1.h"
#include <math.h>
#include <cmath>
double pi = 2 * asin(1.0);

double corner = pi;

const double coords[19][3] = {
    {200, 200, 1 },
    {200, 400, 1},
    {400, 400, 1},
    {400, 200, 1},
    {200, 200, 1},

    {300, 200, 1},
    {300, 250, 1},
    {300, 400, 1},
    {300, 350, 1},
    {200, 300, 1},
    {250, 300, 1},
    {400, 300, 1},
    {350, 300, 1},

    {300, 300, 1},
    {320, 300, 1},
    {380, 240, 1},
    {300, 300, 1},
    {350, 360, 1},
    {320, 300, 1}
};

double coords_clone[19][3] = {
    {200, 200, 1 },
    {200, 400, 1},
    {400, 400, 1},
    {400, 200, 1},
    {200, 200, 1},

    {300, 200, 1},
    {300, 250, 1},
    {300, 400, 1},
    {300, 350, 1},
    {200, 300, 1},
    {250, 300, 1},
    {400, 300, 1},
    {350, 300, 1},

    {300, 300, 1},
    {320, 300, 1},
    {380, 240, 1},
    {300, 300, 1},
    {350, 360, 1},
    {320, 300, 1}
};

double matrix_x[3][3] = {
    {0.4, 0, 0},
    {0,   1, 0},
    {0,   0, 1}
};

double matrix_y[3][3] = {
    {1, 0, 0},
    {0, 1.5, 0},
    {0, 0, 1}
    
};

double matrix_x_to_y[3][3] = {
    { 0, 1, 0 },
    { 1, 0, 0 },
    { 0, 0, 1 }
};

double matrix_rotate[3][3] = {
    { cos (corner), sin(corner), 0},
    { - sin (corner), cos(corner), 0},
    { 0, 0, 1 }
};

double go_home_matrix[3][3] = {
    { 1, 0, 0 },
    { 0, 1, 0 },
    { 600, 600, 1 }
};






#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY3DLAB1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY3DLAB1));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY3DLAB1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY3DLAB1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

void matrix_reset() {
    for (int i = 0; i != 19; i++) {
        for (int j = 0; j != 3; j++) {
            coords_clone[i][j] = coords[i][j];
        }
    }
}

void mult_matrix(double cords[][3], double matum[][3]) {
    double vrem[3] = { 0, 0, 0 };
    for (int i = 0; i != 19; i++) {
        vrem[0] = cords[i][0] * matum[0][0] + cords[i][1] * matum[1][0] + cords[i][2] * matum[2][0];
        vrem[1] = cords[i][0] * matum[0][1] + cords[i][1] * matum[1][1] + cords[i][2] * matum[2][1];
        vrem[2] = cords[i][0] * matum[0][2] + cords[i][1] * matum[1][2] + cords[i][2] * matum[2][2];
        cords[i][0] = vrem[0];
        cords[i][1] = vrem[1];
        cords[i][2] = vrem[2];
    }
}


void draw(double start_coord[][3], HDC hdc)
{
    MoveToEx(hdc,start_coord[0][0], start_coord[0][1], 0);
    for (size_t i = 1; i != 5; i++)
    {
        LineTo(hdc, start_coord[i][0], start_coord[i][1]);
    }
    for (size_t i = 5; i != 15; i += 2)
    {
        MoveToEx(hdc, start_coord[i][0], start_coord[i][1], 0);
        LineTo(hdc, start_coord[i + 1][0], start_coord[i + 1][1]);
    }
    for (size_t i = 15; i != 19; i++)
    {
        LineTo(hdc, start_coord[i][0], start_coord[i][1]);
    }
}


//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{


    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Разобрать выбор в меню:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case x_preobr:
            mult_matrix(coords_clone, matrix_x);
            InvalidateRect(hWnd, NULL, TRUE);
            UpdateWindow(hWnd);
            break;

        case y_preobr:
            mult_matrix(coords_clone, matrix_y);
            InvalidateRect(hWnd, NULL, TRUE);
            UpdateWindow(hWnd);
            break;

        case x_to_y:
            mult_matrix(coords_clone, matrix_x_to_y);
            InvalidateRect(hWnd, NULL, TRUE);
            UpdateWindow(hWnd);
            break;

        case rotate:
            mult_matrix(coords_clone, matrix_rotate);
            mult_matrix(coords_clone, go_home_matrix);
            InvalidateRect(hWnd, NULL, TRUE);
            UpdateWindow(hWnd);
            break;

        case reset:
            matrix_reset();
            InvalidateRect(hWnd, NULL, TRUE);
            UpdateWindow(hWnd);
            break;

        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {

        // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        draw(coords_clone, hdc);

        EndPaint(hWnd, &ps);

    }
        break;
    case WM_DESTROY: 
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
