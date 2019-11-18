DROP DATABASE IF EXISTS BBDDquiz;

CREATE DATABASE BBDDquiz;



USE BBDDquiz;



CREATE TABLE Player(

	username VARCHAR(15) PRIMARY KEY NOT NULL,

	name VARCHAR (15) NOT NULL,

	surname VARCHAR(15),

	email VARCHAR (40),

	pass VARCHAR (15) NOT NULL,

	lvl INTEGER NOT NULL,

	numGamesPlayed INTEGER NOT NULL,

	numGamesWon INTEGER NOT NULL,

	numQuestionsIX INTEGER NOT NULL,

	numQuestionsAERO INTEGER NOT NULL,

	numQuestionsERM INTEGER NOT NULL,

	numQuestionsCA1 INTEGER NOT NULL,

	numQuestionsSO INTEGER NOT NULL,

	numQuestionsMET INTEGER NOT NULL,

	numCorrectQuestionsIX INTEGER NOT NULL,

	numCorrectQuestionsAERO INTEGER NOT NULL,

	numCorrectQuestionsERM INTEGER NOT NULL,

	numCorrectQuestionsCA1 INTEGER NOT NULL,

	numCorrectQuestionsSO INTEGER NOT NULL,

	numCorrectQuestionsMET INTEGER NOT NULL

)ENGINE = InnoDB;





CREATE TABLE Game(

	id INTEGER PRIMARY KEY NOT NULL,

	dategame VARCHAR (15) NOT NULL,

	hourstartgame VARCHAR (15) NOT NULL,

	hourendgame VARCHAR (15) NOT NULL,

	durationgame INTEGER NOT NULL,

	winner VARCHAR (15) NOT NULL,

	2ndplace VARCHAR (15) NOT NULL,

	3rdplace VARCHAR (15) NOT NULL,

	numPlayers INTEGER NOT NULL,

	numGameQuestIX INTEGER NOT NULL,

	numGameQuestAERO INTEGER NOT NULL,

	numGameQuestERM INTEGER NOT NULL,

	numGameQuestCA1 INTEGER NOT NULL,

	numGameQuestSO INTEGER NOT NULL,

	numGameQuestMET INTEGER NOT NULL

)ENGINE = InnoDB;





CREATE TABLE Relation(

	Player VARCHAR (15) NOT NULL,

	Game INTEGER NOT NULL,

	pointsPlayer INTEGER NOT NULL,

	totalPoints INTEGER NOT NULL,

	FOREIGN KEY(Player) REFERENCES Player(username),

	FOREIGN KEY(Game) REFERENCES Game(id)

)ENGINE = InnoDB;







INSERT INTO Player(username, name, surname, email, pass, lvl, numGamesPlayed, numGamesWon, numQuestionsIX, numQuestionsAERO, numQuestionsERM, numQuestionsCA1, numQuestionsSO, numQuestionsMET, numCorrectQuestionsIX, numCorrectQuestionsAERO, numCorrectQuestionsERM, numCorrectQuestionsCA1, numCorrectQuestionsSO, numCorrectQuestionsMET) VALUES ('marmunu', 'Mar', 'Munuera', 'maremeuve@gmail.com', 123, 1, 5, 5, 10, 10, 10, 10, 10, 10, 9,9, 9, 9, 7, 8 );

INSERT INTO Player(username, name, surname, email, pass, lvl, numGamesPlayed, numGamesWon, numQuestionsIX, numQuestionsAERO, numQuestionsERM, numQuestionsCA1, numQuestionsSO, numQuestionsMET, numCorrectQuestionsIX, numCorrectQuestionsAERO, numCorrectQuestionsERM, numCorrectQuestionsCA1, numCorrectQuestionsSO, numCorrectQuestionsMET) VALUES ('albi', 'Alba', 'Gonzalvez', 'agr251299@gmail.com', 222, 1, 5, 5, 10, 10, 10, 10, 10, 10, 9, 8, 9, 7, 7, 6);

INSERT INTO Player(username, name, surname, email, pass, lvl, numGamesPlayed, numGamesWon, numQuestionsIX, numQuestionsAERO, numQuestionsERM, numQuestionsCA1, numQuestionsSO, numQuestionsMET, numCorrectQuestionsIX, numCorrectQuestionsAERO, numCorrectQuestionsERM, numCorrectQuestionsCA1, numCorrectQuestionsSO, numCorrectQuestionsMET) VALUES ('rubencito', 'Ruben', 'Batanero', 'rubenbr1999@gmail.com', 000, 1, 5, 5, 10, 10, 10, 10, 10, 10, 10, 9, 10, 10, 10, 10);



INSERT INTO Game(id, dategame, hourstartgame,hourendgame,durationgame, winner, 2ndplace, 3rdplace, numPlayers, numGameQuestIX, numGameQuestAERO, numGameQuestERM, numGameQuestCA1, numGameQuestSO, numGameQuestMET) VALUES (1, '03/10/2019', '3:00', '3:30', 30,'rubencito', 'albi', 'marmunu', 3, 5, 5, 5, 5, 5, 5);

INSERT INTO Game(id, dategame, hourstartgame,hourendgame,durationgame, winner, 2ndplace, 3rdplace, numPlayers, numGameQuestIX, numGameQuestAERO, numGameQuestERM, numGameQuestCA1, numGameQuestSO, numGameQuestMET) VALUES (2, '03/10/2019', '3:00', '3:30', 30,'rubencito', 'albi', 'marmunu',3, 7, 6, 5, 3, 4, 5);

INSERT INTO Game(id, dategame, hourstartgame,hourendgame,durationgame, winner, 2ndplace, 3rdplace, numPlayers, numGameQuestIX, numGameQuestAERO, numGameQuestERM, numGameQuestCA1, numGameQuestSO, numGameQuestMET) VALUES (3, '03/10/2019', '3:00', '3:30', 30,'marmunu', 'albi', 'rubencito',3, 8, 2, 4, 6, 5, 5);

INSERT INTO Game(id, dategame, hourstartgame,hourendgame,durationgame, winner, 2ndplace, 3rdplace, numPlayers, numGameQuestIX, numGameQuestAERO, numGameQuestERM, numGameQuestCA1, numGameQuestSO, numGameQuestMET) VALUES (4, '04/10/2019', '4:00', '4:30', 30, 'rubencito','marmunu', 'albi', 3, 1, 5, 5, 7, 6, 5);

INSERT INTO Game(id, dategame, hourstartgame,hourendgame,durationgame, winner, 2ndplace, 3rdplace, numPlayers, numGameQuestIX, numGameQuestAERO, numGameQuestERM, numGameQuestCA1, numGameQuestSO, numGameQuestMET) VALUES (5, '04/10/2019', '4:00', '4:30', 30, 'rubencito','marmunu', 'albi', 3, 5, 5, 5, 3, 7, 5);

INSERT INTO Game(id, dategame, hourstartgame,hourendgame,durationgame, winner, 2ndplace, 3rdplace, numPlayers, numGameQuestIX, numGameQuestAERO, numGameQuestERM, numGameQuestCA1, numGameQuestSO, numGameQuestMET) VALUES (6, '04/10/2019', '4:00', '4:30', 30, 'albi','marmunu', 'rubencito', 3, 5, 5, 6, 4, 4, 6);





INSERT INTO Relation(Player, Game, pointsPlayer, totalPoints) VALUES ('marmunu', 2, 20, 50);

INSERT INTO Relation(Player, Game, pointsPlayer, totalPoints) VALUES ('albi', 1, 34, 58);

INSERT INTO Relation(Player, Game, pointsPlayer, totalPoints) VALUES ('rubencito', 3, 13, 53);

INSERT INTO Relation(Player, Game, pointsPlayer, totalPoints) VALUES ('rubencito', 1, 23, 53);

INSERT INTO Relation(Player, Game, pointsPlayer, totalPoints) VALUES ('rubencito', 2, 43, 53);

INSERT INTO Relation(Player, Game, pointsPlayer, totalPoints) VALUES ('albi', 2, 24, 38);

INSERT INTO Relation(Player, Game, pointsPlayer, totalPoints) VALUES ('albi', 3, 14, 58);

INSERT INTO Relation(Player, Game, pointsPlayer, totalPoints) VALUES ('marmunu', 1, 30, 50);

INSERT INTO Relation(Player, Game, pointsPlayer, totalPoints) VALUES ('marmunu', 3, 10, 50);