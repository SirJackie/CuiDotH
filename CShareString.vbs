Public Const PAGE_READWRITE = 4
Public Const FILE_MAP_WRITE = 2
Public Const ERROR_ALREADY_EXISTS = 183&
Public Const ERROR_BAD_ARGUMENTS = 160&
Public Const ERROR_INVALID_DATA = 13&
Public Const GWL_USERDATA = (-21&)
Public Const WM_SETTEXT = &HC
Public Const WM_USER = &H400
Public Const GWL_WNDPROC = (-4)
Public preWndProc As Long
Public Declare Function CallWindowProc Lib "user32" Alias "CallWindowProcA" (ByVal lpPrevWndFunc As Long, ByVal hwnd As Long, ByVal Msg As Long, ByVal wParam As Long, ByVal lParam As Long) As Long
Public Declare Function IsWindowVisible Lib "user32" (ByVal hwnd As Long) As Long
Public Declare Function ShowWindow Lib "user32" (ByVal hwnd As Long, ByVal nCmdShow As Long) As Long
Public Declare Function SetfrmFocus Lib "user32" Alias "SetFocus" (ByVal hwnd As Long) As Long
Public Declare Function FindWindow Lib "user32" Alias "FindWindowA" (ByVal lpClassName As String, ByVal lpWindowName As String) As Long
Public Declare Function PostMessage Lib "user32" Alias "PostMessageA" (ByVal hwnd As Long, ByVal wMsg As Long, ByVal wParam As Long, ByVal lParam As Long) As Long
Public Declare Function SendMessage Lib "user32" Alias "SendMessageA" (ByVal hwnd As Long, ByVal wMsg As Long, ByVal wParam As Long, lParam As Any) As Long
Public Declare Function GetWindowLong Lib "user32" Alias "GetWindowLongA" (ByVal hwnd As Long, ByVal nIndex As Long) As Long
Public Declare Function SetWindowLong Lib "user32" Alias "SetWindowLongA" (ByVal hwnd As Long, ByVal nIndex As Long, ByVal dwNewLong As Long) As Long
Public Declare Function SetWindowText Lib "user32" Alias "SetWindowTextA" (ByVal hwnd As Long, ByVal lpString As String) As Long
Public Declare Function FindWindowEx Lib "user32" Alias "FindWindowExA" (ByVal hWnd1 As Long, ByVal hWnd2 As Long, ByVal lpsz1 As String, ByVal lpsz2 As String) As Long
Public Declare Function CreateFileMapping Lib "kernel32" Alias "CreateFileMappingA" (ByVal hFile As Long, lpFileMappigAttributes As Any, ByVal flProtect As Long, ByVal dwMaximumSizeHigh As Long, ByVal dwMaximumSizeLow As Long, ByVal lpName As String) As Long
Public Declare Function CloseHandle Lib "kernel32" (ByVal hObject As Long) As Long
Public Declare Function MapViewOfFile Lib "kernel32" (ByVal hFileMappingObject As Long, ByVal dwDesiredAccess As Long, ByVal dwFileOffsetHigh As Long, ByVal dwFileOffsetLow As Long, ByVal dwNumberOfBytesToMap As Long) As Long
Public Declare Function UnmapViewOfFile Lib "kernel32" (lpBaseAddress As Any) As Long
Public Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (Destination As Any, Source As Any, ByVal length As Long)
Public Declare Sub CopyMemoryToStr Lib "kernel32" Alias "RtlMoveMemory" (ByVal strDst As String, pScr As Long, ByVal length As Long)
Public Declare Sub CopyMemoryStr Lib "kernel32" Alias "RtlMoveMemory" (strDst As Long, ByVal pScr As String, ByVal length As Long)
Public pipe As Long     ' 内存映射句柄
Public pBuffer As Long  ' 内存映射Buffer

Function CreateSM(strName As String) As Long
    CreateSM = CreateFileMapping(-1, Null, PAGE_READWRITE, 0, 65535, strName)
End Function

Sub CloseSM(pipe As Long)
    CloseHandle pipe
End Sub

Function ReadSM(pipe As Long, pos)

    If pipe = -1 Then
    
        ' 打开失败,说明管道已经关闭,返回-1
        MsgBox ("Pipe doesn't exist!")
        ReadSM = -1
        
    Else
    
        ' 创建Buffer
        pBuffer = MapViewOfFile(pipe, FILE_MAP_WRITE, 0, 0, 0)
        
        ' 强制类型转换
        Dim longPos As Long
        longPos = pos
        
        ' 取出Buffer指定位置的数据
        Dim data As Long
        CopyMemory data, ByVal (pBuffer + longPos), 4
        
        ' 删除Buffer
        UnmapViewOfFile pBuffer
        
        ' 返回读出的数据
        ReadSM = data
        
    End If
    
End Function

Function WriteSM(pipe As Long, pos, data)

    If pipe = -1 Then
    
        ' 打开失败,说明管道已经关闭,返回-1(失败)
        MsgBox ("Pipe doesn't exist!")
        WriteSM = -1
        
    Else
    
        ' 创建Buffer
        pBuffer = MapViewOfFile(pipe, FILE_MAP_WRITE, 0, 0, 0)
        
        ' 强制类型转换
        Dim longData As Long
        longData = data
        Dim longPos As Long
        longPos = pos
        
        ' 将data写入到Buffer的指定位置
        CopyMemory ByVal (pBuffer + longPos), longData, 4
        
        ' 删除Buffer
        UnmapViewOfFile pBuffer
        
        ' 返回0(成功)
        WriteSM = 0
        
    End If
    
End Function