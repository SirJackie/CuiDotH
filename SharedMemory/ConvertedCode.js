var code = "Public Const PAGE_READWRITE = 4\nPublic Const FILE_MAP_WRITE = 2\nPublic Const ERROR_ALREADY_EXISTS = 183&\nPublic Const ERROR_BAD_ARGUMENTS = 160&\nPublic Const ERROR_INVALID_DATA = 13&\nPublic Const GWL_USERDATA = (-21&)\nPublic Const WM_SETTEXT = &HC\nPublic Const WM_USER = &H400\nPublic Const GWL_WNDPROC = (-4)\nPublic preWndProc As Long\n\n#If VBA7 And Win64 Then\nPublic Declare PtrSafe Function CallWindowProc Lib \"user32\" Alias \"CallWindowProcA\" (ByVal lpPrevWndFunc As Long, ByVal hwnd As Long, ByVal Msg As Long, ByVal wParam As Long, ByVal lParam As Long) As Long\nPublic Declare PtrSafe Function IsWindowVisible Lib \"user32\" (ByVal hwnd As Long) As Long\nPublic Declare PtrSafe Function ShowWindow Lib \"user32\" (ByVal hwnd As Long, ByVal nCmdShow As Long) As Long\nPublic Declare PtrSafe Function SetfrmFocus Lib \"user32\" Alias \"SetFocus\" (ByVal hwnd As Long) As Long\nPublic Declare PtrSafe Function FindWindow Lib \"user32\" Alias \"FindWindowA\" (ByVal lpClassName As String, ByVal lpWindowName As String) As Long\nPublic Declare PtrSafe Function PostMessage Lib \"user32\" Alias \"PostMessageA\" (ByVal hwnd As Long, ByVal wMsg As Long, ByVal wParam As Long, ByVal lParam As Long) As Long\nPublic Declare PtrSafe Function SendMessage Lib \"user32\" Alias \"SendMessageA\" (ByVal hwnd As Long, ByVal wMsg As Long, ByVal wParam As Long, lParam As Any) As Long\nPublic Declare PtrSafe Function GetWindowLong Lib \"user32\" Alias \"GetWindowLongA\" (ByVal hwnd As Long, ByVal nIndex As Long) As Long\nPublic Declare PtrSafe Function SetWindowLong Lib \"user32\" Alias \"SetWindowLongA\" (ByVal hwnd As Long, ByVal nIndex As Long, ByVal dwNewLong As Long) As Long\nPublic Declare PtrSafe Function SetWindowText Lib \"user32\" Alias \"SetWindowTextA\" (ByVal hwnd As Long, ByVal lpString As String) As Long\nPublic Declare PtrSafe Function FindWindowEx Lib \"user32\" Alias \"FindWindowExA\" (ByVal hWnd1 As Long, ByVal hWnd2 As Long, ByVal lpsz1 As String, ByVal lpsz2 As String) As Long\nPublic Declare PtrSafe Function CreateFileMapping Lib \"kernel32\" Alias \"CreateFileMappingA\" (ByVal hFile As Long, lpFileMappigAttributes As Any, ByVal flProtect As Long, ByVal dwMaximumSizeHigh As Long, ByVal dwMaximumSizeLow As Long, ByVal lpName As String) As Long\nPublic Declare PtrSafe Function CloseHandle Lib \"kernel32\" (ByVal hObject As Long) As Long\nPublic Declare PtrSafe Function MapViewOfFile Lib \"kernel32\" (ByVal hFileMappingObject As Long, ByVal dwDesiredAccess As Long, ByVal dwFileOffsetHigh As Long, ByVal dwFileOffsetLow As Long, ByVal dwNumberOfBytesToMap As Long) As Long\nPublic Declare PtrSafe Function UnmapViewOfFile Lib \"kernel32\" (lpBaseAddress As Any) As Long\nPublic Declare PtrSafe Sub CopyMemory Lib \"kernel32\" Alias \"RtlMoveMemory\" (Destination As Any, Source As Any, ByVal length As Long)\nPublic Declare PtrSafe Sub CopyMemoryToStr Lib \"kernel32\" Alias \"RtlMoveMemory\" (ByVal strDst As String, pScr As Long, ByVal length As Long)\nPublic Declare PtrSafe Sub CopyMemoryStr Lib \"kernel32\" Alias \"RtlMoveMemory\" (strDst As Long, ByVal pScr As String, ByVal length As Long)\n#Else\nPublic Declare Function CallWindowProc Lib \"user32\" Alias \"CallWindowProcA\" (ByVal lpPrevWndFunc As Long, ByVal hwnd As Long, ByVal Msg As Long, ByVal wParam As Long, ByVal lParam As Long) As Long\nPublic Declare Function IsWindowVisible Lib \"user32\" (ByVal hwnd As Long) As Long\nPublic Declare Function ShowWindow Lib \"user32\" (ByVal hwnd As Long, ByVal nCmdShow As Long) As Long\nPublic Declare Function SetfrmFocus Lib \"user32\" Alias \"SetFocus\" (ByVal hwnd As Long) As Long\nPublic Declare Function FindWindow Lib \"user32\" Alias \"FindWindowA\" (ByVal lpClassName As String, ByVal lpWindowName As String) As Long\nPublic Declare Function PostMessage Lib \"user32\" Alias \"PostMessageA\" (ByVal hwnd As Long, ByVal wMsg As Long, ByVal wParam As Long, ByVal lParam As Long) As Long\nPublic Declare Function SendMessage Lib \"user32\" Alias \"SendMessageA\" (ByVal hwnd As Long, ByVal wMsg As Long, ByVal wParam As Long, lParam As Any) As Long\nPublic Declare Function GetWindowLong Lib \"user32\" Alias \"GetWindowLongA\" (ByVal hwnd As Long, ByVal nIndex As Long) As Long\nPublic Declare Function SetWindowLong Lib \"user32\" Alias \"SetWindowLongA\" (ByVal hwnd As Long, ByVal nIndex As Long, ByVal dwNewLong As Long) As Long\nPublic Declare Function SetWindowText Lib \"user32\" Alias \"SetWindowTextA\" (ByVal hwnd As Long, ByVal lpString As String) As Long\nPublic Declare Function FindWindowEx Lib \"user32\" Alias \"FindWindowExA\" (ByVal hWnd1 As Long, ByVal hWnd2 As Long, ByVal lpsz1 As String, ByVal lpsz2 As String) As Long\nPublic Declare Function CreateFileMapping Lib \"kernel32\" Alias \"CreateFileMappingA\" (ByVal hFile As Long, lpFileMappigAttributes As Any, ByVal flProtect As Long, ByVal dwMaximumSizeHigh As Long, ByVal dwMaximumSizeLow As Long, ByVal lpName As String) As Long\nPublic Declare Function CloseHandle Lib \"kernel32\" (ByVal hObject As Long) As Long\nPublic Declare Function MapViewOfFile Lib \"kernel32\" (ByVal hFileMappingObject As Long, ByVal dwDesiredAccess As Long, ByVal dwFileOffsetHigh As Long, ByVal dwFileOffsetLow As Long, ByVal dwNumberOfBytesToMap As Long) As Long\nPublic Declare Function UnmapViewOfFile Lib \"kernel32\" (lpBaseAddress As Any) As Long\nPublic Declare Sub CopyMemory Lib \"kernel32\" Alias \"RtlMoveMemory\" (Destination As Any, Source As Any, ByVal length As Long)\nPublic Declare Sub CopyMemoryToStr Lib \"kernel32\" Alias \"RtlMoveMemory\" (ByVal strDst As String, pScr As Long, ByVal length As Long)\nPublic Declare Sub CopyMemoryStr Lib \"kernel32\" Alias \"RtlMoveMemory\" (strDst As Long, ByVal pScr As String, ByVal length As Long)\n#End If\n\nPublic pipe As Long ' 内存映射句柄\nPublic pBuffer As Long  ' 内存映射Buffer\n\nFunction CreateSM(strName As String) As Long\nDim negativeone As Long\nnegativeone = -1\nCreateSM = CreateFileMapping(negativeone, Null, PAGE_READWRITE, 0, 65535, strName)\nEnd Function\n\nSub CloseSM(pipe As Long)\nCloseHandle pipe\nEnd Sub\n\nFunction ReadSM(pipe As Long, pos)\n\nIf pipe = -1 Then\n\n' 打开失败,说明管道已经关闭,返回-1\nMsgBox (\"Pipe doesn't exist!\")\nReadSM = -1\n\nElse\n\n' 创建Buffer\npBuffer = MapViewOfFile(pipe, FILE_MAP_WRITE, 0, 0, 0)\n\n' 强制类型转换\nDim longPos As Long\nlongPos = pos\n\n' 取出Buffer指定位置的数据\nDim data As Long\nCopyMemory data, ByVal (pBuffer + longPos), 4\n\n' 删除Buffer\nUnmapViewOfFile pBuffer\n\n' 返回读出的数据\nReadSM = data\n\nEnd If\n\nEnd Function\n\nFunction WriteSM(pipe As Long, pos, data)\n\nIf pipe = -1 Then\n\n' 打开失败,说明管道已经关闭,返回-1(失败)\nMsgBox (\"Pipe doesn't exist!\")\nWriteSM = -1\n\nElse\n\n' 创建Buffer\npBuffer = MapViewOfFile(pipe, FILE_MAP_WRITE, 0, 0, 0)\n\n' 强制类型转换\nDim longData As Long\nlongData = data\nDim longPos As Long\nlongPos = pos\n\n' 将data写入到Buffer的指定位置\nCopyMemory ByVal (pBuffer + longPos), longData, 4\n\n' 删除Buffer\nUnmapViewOfFile pBuffer\n\n' 返回0(成功)\nWriteSM = 0\n\nEnd If\n\nEnd Function\n"
