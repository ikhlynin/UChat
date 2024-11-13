CREATE TABLE IF NOT EXISTS `chat` (
  `idchar` INTEGER PRIMARY KEY AUTOINCREMENT,
  `Name` TEXT DEFAULT NULL,
  `Users` TEXT DEFAULT NULL,
  `Admin` TEXT DEFAULT NULL,
  `Path` TEXT DEFAULT 'icon.png',
  `Status` INTEGER DEFAULT NULL
);

CREATE TABLE IF NOT EXISTS `user` (
  `iduser` INTEGER PRIMARY KEY AUTOINCREMENT,
  `Login` TEXT DEFAULT NULL,
  `Password` TEXT DEFAULT NULL,
  `Name` TEXT DEFAULT NULL,
  `ActivityTime` TEXT DEFAULT NULL,
  `Boi` TEXT DEFAULT NULL,
  `Status` INTEGER DEFAULT NULL,
  `Foto` TEXT DEFAULT 'avatar.png'
);

CREATE TABLE IF NOT EXISTS `message` (
  `idmessage` INTEGER PRIMARY KEY AUTOINCREMENT,
  `chat_idchar` INTEGER NOT NULL,
  `text` TEXT DEFAULT NULL,
  `Sender` INTEGER DEFAULT NULL,
  `Time` TEXT DEFAULT NULL,
  `messagecol` TEXT DEFAULT NULL,
  FOREIGN KEY (`chat_idchar`)
    REFERENCES `chat` (`idchar`)
);

CREATE TABLE IF NOT EXISTS `user_has_chat` (
  `user_iduser` INTEGER NOT NULL,
  `chat_idchar` INTEGER NOT NULL,
  PRIMARY KEY (`user_iduser`,`chat_idchar`),
  FOREIGN KEY (`chat_idchar`)
    REFERENCES `chat` (`idchar`),
  FOREIGN KEY (`user_iduser`)
    REFERENCES `user` (`iduser`)
);
