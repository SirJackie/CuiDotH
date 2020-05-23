Option Explicit
'***********************************************************************
'Class Module Name: CShareString
'Refactored by AdamBear 2002-1-31 22:00
'Originally Created By Bruce Meckinney, HardCore Visual Basic
'Purpose: Demostrate the FileMapping and Inter-Process Community
'************************************************************************

'************************************************************************
'修正了原来代码的一个错误，不过错误原因不知，问题涉及到DBCS和UNICODE转换
'现象：内部自动转换回UNICODE时只返回了该串的DBCS长度部分。
'     如: "Adam苯蛋Bear" 长度为10，返回却是"Adam笨蛋Be"长度为8，是其在DBCS
'中的长度
' 临时解决方案：将原串放大一倍，再重新计算长度，并截取。
' 经验：不要过于相信大师的代码，他也不一定把所有问题都考虑了。
'************************************************************************
Private Const PAGE_READWRITE = 4
Private Const FILE_MAP_WRITE = 2
Private Const ERROR_ALREADY_EXISTS = 183&
Private Const ERROR_BAD_ARGUMENTS = 160&
Private Const ERROR_INVALID_DATA = 13&
Private Const GWL_USERDATA = (-21&)
Private Const WM_SETTEXT = &HC
Private Const WM_USER = &H400
Private Const GWL_WNDPROC = (-4)
Private preWndProc As Long
Private Declare Function CallWindowProc Lib "user32" Alias "CallWindowProcA" (ByVal lpPrevWndFunc As Long, ByVal hwnd As Long, ByVal Msg As Long, ByVal wParam As Long, ByVal lParam As Long) As Long
Private Declare Function IsWindowVisible Lib "user32" (ByVal hwnd As Long) As Long
Private Declare Function ShowWindow Lib "user32" (ByVal hwnd As Long, ByVal nCmdShow As Long) As Long
Private Declare Function SetfrmFocus Lib "user32" Alias "SetFocus" (ByVal hwnd As Long) As Long
Private Declare Function FindWindow Lib "user32" Alias "FindWindowA" (ByVal lpClassName As String, ByVal lpWindowName As String) As Long
Private Declare Function PostMessage Lib "user32" Alias "PostMessageA" (ByVal hwnd As Long, ByVal wMsg As Long, ByVal wParam As Long, ByVal lParam As Long) As Long
Private Declare Function SendMessage Lib "user32" Alias "SendMessageA" (ByVal hwnd As Long, ByVal wMsg As Long, ByVal wParam As Long, lParam As Any) As Long
Private Declare Function GetWindowLong Lib "user32" Alias "GetWindowLongA" (ByVal hwnd As Long, ByVal nIndex As Long) As Long
Private Declare Function SetWindowLong Lib "user32" Alias "SetWindowLongA" (ByVal hwnd As Long, ByVal nIndex As Long, ByVal dwNewLong As Long) As Long
Private Declare Function SetWindowText Lib "user32" Alias "SetWindowTextA" (ByVal hwnd As Long, ByVal lpString As String) As Long
Private Declare Function FindWindowEx Lib "user32" Alias "FindWindowExA" (ByVal hWnd1 As Long, ByVal hWnd2 As Long, ByVal lpsz1 As String, ByVal lpsz2 As String) As Long
Private Declare Function CreateFileMapping Lib "kernel32" Alias "CreateFileMappingA" (ByVal hFile As Long, lpFileMappigAttributes As Any, ByVal flProtect As Long, ByVal dwMaximumSizeHigh As Long, ByVal dwMaximumSizeLow As Long, ByVal lpName As String) As Long
Private Declare Function CloseHandle Lib "kernel32" (ByVal hObject As Long) As Long
Private Declare Function MapViewOfFile Lib "kernel32" (ByVal hFileMappingObject As Long, ByVal dwDesiredAccess As Long, ByVal dwFileOffsetHigh As Long, ByVal dwFileOffsetLow As Long, ByVal dwNumberOfBytesToMap As Long) As Long
Private Declare Function UnmapViewOfFile Lib "kernel32" (lpBaseAddress As Any) As Long
Private Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (Destination As Any, Source As Any, ByVal length As Long)
Private Declare Sub CopyMemoryToStr Lib "kernel32" Alias "RtlMoveMemory" (ByVal strDst As String, pScr As Long, ByVal length As Long)
Private Declare Sub CopyMemoryStr Lib "kernel32" Alias "RtlMoveMemory" (strDst As Long, ByVal pScr As String, ByVal length As Long)
Private 内存映射句柄 As Long                      '内存映射句柄
Private 映射视图指针 As Long                      '映射视图指针

Sub 共享名称(strName As String)
    Dim e As Long
    If strName = "" Then ApiRaise ERROR_BAD_ARGUMENTS
    ' 尝试建立一个大小为64K内存文件映射，不要怕设得大了，因为使用时是按4K为单位分配的。
    内存映射句柄 = CreateFileMapping(-1, ByVal Null指针, PAGE_READWRITE, 0, 65535, strName)
    '保存错误描述，因其不一定真是错误，此处可能是正常的文件已存在信息，
    '   具体可参见CreateFileMapping的帮助文件
    e = Err.LastDllError
    If 内存映射句柄 = 0 Then ApiRaise e    '当然对CreateFileMapping这API，我们可以认为返回0才是错误。
    ' 取得映射文件的视图指针p，它指向就是从共享内存文件中映射来的进程可用的内存。
    映射视图指针 = MapViewOfFile(内存映射句柄, FILE_MAP_WRITE, 0, 0, 0)
    If 映射视图指针 = Null指针 Then
        CloseHandle 内存映射句柄   '一定要注意
        ApiRaise Err.LastDllError
    End If
    If e <> ERROR_ALREADY_EXISTS Then
        'HACK BSTR 保存p的前四个字节作为BSTR的长度存放处。
        CopyMemory ByVal 映射视图指针, 0, 4
    Else
        '返回的是已经存在的FileMapping的句柄，不是错误
        'ApiRaise ERROR_ALREADY_EXISTS
    End If
End Sub

Private Sub Class_Terminate()
    '清理，重要，否则会有内存漏洞。
    '    当然，注释掉这两句话有时也有奇妙的用处，你可以在内存中留下东西，只要不重新起动Windows，
    '当程序再次起动后，还可以访问上次留下的内容。谁知道有什么用！
    UnmapViewOfFile 映射视图指针
    CloseHandle 内存映射句柄
End Sub

'NOTE:为了让本类能做为String类型处理，须将本过程属性设为缺省。
Property Get item() As String
    If 内存映射句柄 = 0 Then ErrRaise ERROR_INVALID_DATA
    BugAssert 映射视图指针 <> Null指针
    Dim c As Long
    '取出BSTR的长度
    CopyMemory c, ByVal 映射视图指针, 4
    If c Then
        ' 由于未知原因，此处先将字符串放大一倍
        item = String$(c * 2, " ")
        CopyMemoryToStr item, ByVal (映射视图指针 + 4), c * 2
        Dim pos As Long
        pos = InStr(item, Chr(0))
        If pos Then item = Left(item, pos - 1)
    End If
End Property

Property Let item(s As String)
    If 内存映射句柄 = 0 Then ErrRaise ERROR_INVALID_DATA
    BugAssert 映射视图指针 <> Null指针
    Dim c As Long ', ab() As Byte
    c = Len(s)
    'ab = StrConv(s, vbFromUnicode) & vbNullChar
    ' 重新将BSTR放回内存中
    CopyMemory ByVal 映射视图指针, c, 4
    CopyMemoryStr ByVal (映射视图指针 + 4), s, c * 2
End Property
'

Private Sub ErrRaise(e As Long)
    Dim sSource As String
    If e > 1000 Then
        sSource = App.EXEName & ".SharedString"
        Err.Raise COMError(e), sSource
    Else
        sSource = App.EXEName & ".VBError"
        Err.Raise e, sSource
    End If
End Sub

Private Function WndProc(ByVal hwnd As Long, ByVal Msg As Long, ByVal wParam As Long, ByVal lParam As Long) As Long
    On Error Resume Next
    If (Msg = WM_USER + 112) Then
        With frmTest
            If frmTest.WindowState = 1 Then
                .WindowState = 0
           
            End If
            .Visible = True
            SetfrmFocus frmTest.hwnd
        End With
    End If
    WndProc = CallWindowProc(preWndProc, hwnd, Msg, wParam, lParam)
End Function