Sub TokenizeSeriousCode()
    Dim filePath As String, line As String, token As String
    Dim fileNum As Integer, outputFile As Integer
    Dim tokens As Collection, lineTokens As Collection
    Set tokens = New Collection
    
    filePath = "C:\path\to\code.serious"
    fileNum = FreeFile
    outputFile = FreeFile + 1
    
    Open filePath For Input As #fileNum
    Do While Not EOF(fileNum)
        Line Input #fileNum, line
        Set lineTokens = ParseLineToTokens(line)
        For Each token In lineTokens
            tokens.Add token
        Next
    Loop
    Close #fileNum
    
    WriteTokensToJSON tokens, "C:\path\to\tokens.json"
End Sub

Function ParseLineToTokens(line As String) As Collection
    Dim lineTokens As New Collection
    Dim word As String
    
    Dim keywordList As Variant
    keywordList = Array("let", "announce", "if", "for", "async", "restrict", "~", "^", "{", "}", "true", "false")
    
    Dim words() As String
    words = Split(line, " ")
    
    For Each word In words
        If word Like "[A-Za-z][A-Za-z0-9_]*" Then
            If IsInArray(LCase(word), keywordList) Then
                lineTokens.Add "KEYWORD: " & UCase(word)
            Else
                lineTokens.Add "IDENTIFIER: " & word
            End If
        ElseIf IsNumeric(word) Then
            lineTokens.Add "INT_LITERAL: " & word
        ElseIf word = "+" Or word = "-" Or word = "*" Then
            lineTokens.Add "OPERATOR: " & word
        End If
    Next
    
    Set ParseLineToTokens = lineTokens
End Function

Function IsInArray(value As String, arr As Variant) As Boolean
    Dim i As Integer
    IsInArray = False
    For i = LBound(arr) To UBound(arr)
        If arr(i) = value Then
            IsInArray = True
            Exit Function
        End If
    Next i
End Function

Sub WriteTokensToJSON(tokens As Collection, outputPath As String)
    Dim outputFile As Integer
    outputFile = FreeFile
    Open outputPath For Output As #outputFile
    
    Print #outputFile, "{""tokens"": ["
    Dim token As Variant
    For Each token In tokens
        Print #outputFile, """" & token & ""","
    Next
    Print #outputFile, "]}"
    
    Close #outputFile
End Sub
