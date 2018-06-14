unit TokenU;


interface

  function DateTimeToUnix(ConvDate: TDateTime): Longint;
  
  // Структура хранения токенов
  type
    TokenStore = record
            Code: string;
            Token: string;
            Refresh_Token: string;
            socket_token: string;
            TokenExpire: integer;
  end;


var
    UnixStartDate: TDateTime = 25569.0;
    Token : TokenStore;


implementation
  // Функция для преобразования времени в UNIX подобное
  function DateTimeToUnix(ConvDate: TDateTime): Longint;
  begin
    Result := Round((ConvDate - UnixStartDate) * 86400);
  end;

end.
