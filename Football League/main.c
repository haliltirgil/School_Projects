#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define MAXTEAMS 40
#define MAXMATCHES 30




                        // 375829 Salih Azakli
                        // 348357 Halil İbrahim Tirgil


struct settings
{
        int numberofTeams;
        int winPoint;
        int drawPoint;
        int lossPoint;
}league;


struct team
{
        char name[15];
        char shortName;
        int win, draw, loss;
        int goalsFor, goalsAgainst;
        int pts, rank;
        int playedMatch;
        int average;


}teams[MAXTEAMS], temp;


struct match
{
        char homeTeam;
        char awayTeam;
        int homeGoals;
        int awayGoals;
}matches[MAXMATCHES];




int findError(int noMatches, char home, char away);
void readSettings();
void readTeams();
void readMatches();
void addTeamwthKeyboard();
void addMatchwthKeyboard();
void changeSettings();
void setAverage();
void leagueTable();
void menu();


int main()
{
        setlocale(LC_ALL, "Turkish");


        menu();


        return 0;
}


int findError(int noMatches, char home, char away)
{
        for (int i = 0; i < noMatches; i++)
        {
                if (matches[i].homeTeam == home && matches[i].awayTeam == away)
                {
                        return 1;
                }
        }
        return 0;
}


void readSettings()
{
        FILE *settingsptr;
        settingsptr = fopen("ayarlar.txt", "r");


        if (settingsptr == NULL)
        {
                printf("Dosya bulunamadi.");
        }
        else
        {
                for (int i = 0; !feof(settingsptr); i++)
                {
                        fscanf(settingsptr, "%d %d %d %d", &league.numberofTeams, &league.winPoint, &league.drawPoint, &league.lossPoint);
                }


        }
        fclose(settingsptr);
}


void readTeams()
{
        int teamCounter = 0;


        FILE *teamsptr;
        teamsptr = fopen("takimlar.txt", "r");


        if (teamsptr == NULL)
        {
                printf("Dosya bulunamadi.");
        }
        else
        {
                for (int i = 0; !feof(teamsptr); i++)
                {
                        fscanf(teamsptr, "%s", &teams[i].name);
                        teams[i].shortName = (char)(65 + i);
                        teamCounter++;
                }


        }
        fclose(teamsptr);
}


void readMatches()
{
        int numberofMatches = 0;
        int home_Team;
        int away_Team;


        FILE *matchesptr;
        matchesptr = fopen("maclar1.txt", "r");


        if (matchesptr == NULL)
        {
                printf("Dosya bulunamadi.\n");
        }
        else
        {


                for (int i = 0; !feof(matchesptr); i++)
                {
                        fscanf(matchesptr, "%s %d %s %d", &matches[i].homeTeam, &matches[i].homeGoals, &matches[i].awayTeam, &matches[i].awayGoals);


                        if (!findError(numberofMatches, matches[i].homeTeam, matches[i].awayTeam))
                        {




                                home_Team = matches[i].homeTeam - 65;
                                away_Team = matches[i].awayTeam - 65;


                                if (matches[i].homeGoals > matches[i].awayGoals)
                                {
                                        teams[home_Team].win++;
                                        teams[home_Team].pts += league.winPoint;
                                        teams[home_Team].goalsFor += matches[i].homeGoals;
                                        teams[home_Team].goalsAgainst += matches[i].awayGoals;
                                        teams[home_Team].playedMatch++;
                                        teams[away_Team].loss++;
                                        teams[away_Team].pts += league.lossPoint;
                                        teams[away_Team].goalsFor += matches[i].awayGoals;
                                        teams[away_Team].goalsAgainst += matches[i].homeGoals;
                                        teams[away_Team].playedMatch++;




                                }
                                else if (matches[i].homeGoals == matches[i].awayGoals)
                                {
                                        teams[home_Team].draw++;
                                        teams[home_Team].pts += league.drawPoint;
                                        teams[home_Team].goalsFor += matches[i].homeGoals;
                                        teams[home_Team].goalsAgainst += matches[i].awayGoals;
                                        teams[home_Team].playedMatch++;
                                        teams[away_Team].draw++;
                                        teams[away_Team].pts += league.drawPoint;
                                        teams[away_Team].goalsFor += matches[i].awayGoals;
                                        teams[away_Team].goalsAgainst += matches[i].homeGoals;
                                        teams[away_Team].playedMatch++;


                                }
                                else
                                {
                                        teams[away_Team].win++;
                                        teams[away_Team].pts += league.winPoint;
                                        teams[away_Team].goalsFor += matches[i].awayGoals;
                                        teams[away_Team].goalsAgainst += matches[i].homeGoals;
                                        teams[away_Team].playedMatch++;
                                        teams[home_Team].loss++;
                                        teams[home_Team].pts += league.lossPoint;
                                        teams[home_Team].goalsFor += matches[i].homeGoals;
                                        teams[home_Team].goalsAgainst += matches[i].awayGoals;
                                        teams[home_Team].playedMatch++;
                                }


                                numberofMatches++;
                        }
                        else
                        {
                                printf("%c ile %c  takimlari daha once oynamistir\n", matches[i].homeTeam, matches[i].awayTeam);
                                matches[i].homeTeam = 0;
                                matches[i].homeGoals = 0;
                                matches[i].awayTeam = 0;
                                matches[i].awayGoals = 0;
                                i--;
                        }
                }
        }
        fclose(matchesptr);
}


void addTeamwthKeyboard()
{
        readSettings();
        readTeams();


        FILE *settingsptr;
        FILE *newsettingsptr;


        char newteam[15];
        printf("Lutfen bir takim ekleyiniz:");
        scanf("%s", &newteam);


        FILE *addteamsptr;
        addteamsptr = fopen("takimlar.txt", "a");


        if (addteamsptr == NULL)
        {
                printf("Dosya bulunamadi.\n");
        }
        else
        {
                int equality = 0;
                int j;


                for (int i = 0; i < league.numberofTeams; i++)
                {
                        for (j = 0; j < newteam[j] != '\0'; j++)
                        {
                                if (newteam[j] == teams[i].name[j])
                                {
                                        equality = 1;
                                }
                                else
                                {
                                        equality = 0;
                                        break;
                                }
                        }


                        if (equality == 1 && teams[i].name[j] == '\0')
                        {
                                printf("Bu isimde takim listede mevcuttur.\n\n");
                                break;


                        }
                        else if (i == league.numberofTeams - 1)
                        {
                                fprintf(addteamsptr, "\n%s", newteam);
                                printf("%s takimi listeye basari ile eklenmistir.\n\n", newteam);


                                remove("ayarlar.txt");
                                newsettingsptr = fopen("ayarlar.txt", "w");


                                if (newsettingsptr == NULL)
                                {
                                        printf("Dosya bulunamadi.");
                                }
                                else
                                {


                                        fprintf(newsettingsptr, "%d\n%d\n%d\n%d", league.numberofTeams + 1, league.winPoint, league.drawPoint, league.lossPoint);


                                        fclose(newsettingsptr);
                                        break;


                                }
                        }
                }
        }
        fclose(addteamsptr);
}


void addMatchwthKeyboard()
{
        readSettings();
        readMatches();


        char newhmtm;
        char newhmgl;
        char newaytm;
        char newaygl;
        FILE *addmatchesptr;


        addmatchesptr = fopen("maclar1.txt", "a");


        if (addmatchesptr == NULL)
        {
                printf("Dosya bulunamadi.\n");
        }
        else
        {
                printf("Maci ekleyiniz: ");
                scanf("%c %c %c %c %c",&newhmtm, &newhmtm, &newhmgl, &newaytm, &newaygl);




                for (int i = 0; i < league.numberofTeams; i++)
                {
                        if (matches[i].homeTeam == newhmtm  && matches[i].awayTeam == newaytm)
                        {
                                printf("bu mac zaten listede bulunmaktadir.\n");
                                break;
                        }
                        else if (i == league.numberofTeams - 1)
                        {
                                fprintf(addmatchesptr, "\n%c %c %c %c", newhmtm, newhmgl, newaytm, newaygl);
                                printf("Mac basari ile eklenmistir.\n");
                        }
                }
        }
        fclose(addmatchesptr);
}


void changeSettings()
{
        readSettings();


        FILE *settingsptr;
        FILE *newsettingsptr;


        int selection;
        int newNoT;
        int newWP, newDP, newLP;


        puts("[1]Galibiyet puanini degistirme");
        puts("[2]Beraberlik puanini degistirme");
        puts("[3]Maglubiyet puanini degistirme");


        printf("\nYapmak istediginiz islemi belirtiniz:");
        scanf("%d", &selection);


        system("CLS");


        if (selection < 1 || selection>3)
        {
                printf("Gecersiz secim yaptiniz.\n");
        }
        else
        {
                switch (selection)
                {
                case 1:


                        puts("Mevcut ayarlar girdileri:");
                        printf("%d\n%d\n%d\n%d\n", league.numberofTeams, league.winPoint, league.drawPoint, league.lossPoint);


                        remove("settingsptr");


                        printf("Yeni galibiyet puanini giriniz:");
                        scanf("%d", &newWP);


                        system("CLS");


                        newsettingsptr = fopen("ayarlar.txt", "w");


                        if (newsettingsptr == NULL)
                        {
                                printf("Boyle bir dosya yok.");
                        }
                        else
                        {
                                fprintf(newsettingsptr, "%d\n%d\n%d\n%d ", league.numberofTeams, newWP, league.drawPoint, league.lossPoint);


                        }
                        league.winPoint = newWP;


                        fclose(newsettingsptr);
                        break;


                case 2:


                        puts("Mevcut ayarlar girdileri:");
                        printf("%d\n%d\n%d\n%d\n", league.numberofTeams, league.winPoint, league.drawPoint, league.lossPoint);


                        remove("settingsptr");


                        printf("Yeni beraberlik puanini giriniz:");
                        scanf("%d", &newDP);


                        system("CLS");


                        newsettingsptr = fopen("ayarlar.txt", "w");


                        if (newsettingsptr == NULL)
                        {
                                printf("Boyle bir dosya yok.");
                        }
                        else
                        {
                                fprintf(newsettingsptr, "%d\n%d\n%d\n%d ", league.numberofTeams, league.winPoint, newDP, league.lossPoint);


                        }
                        league.drawPoint = newDP;


                        fclose(newsettingsptr);
                        break;
                case 3:


                        puts("Mevcut ayarlar girdileri:");
                        printf("%d\n%d\n%d\n%d\n", league.numberofTeams, league.winPoint, league.drawPoint, league.lossPoint);


                        remove("settingsptr");


                        printf("Yeni maglubiyet puanini giriniz:");
                        scanf("%d", &newLP);


                        system("CLS");


                        newsettingsptr = fopen("ayarlar.txt", "w");


                        if (newsettingsptr == NULL)
                        {
                                printf("Boyle bir dosya yok.");
                        }
                        else
                        {
                                fprintf(newsettingsptr, "%d\n%d\n%d\n%d ", league.numberofTeams, league.winPoint, league.drawPoint, newLP);
                        }
                        league.lossPoint = newLP;


                        fclose(newsettingsptr);
                        break;
                default:
                        break;
                }
        }
}


void setAverage()
{
        for (int i = 0; i < league.numberofTeams; i++)
        {
                teams[i].average = teams[i].goalsFor - teams[i].goalsAgainst;
        }
}


void leagueTable()
{
        readSettings();
        readTeams();
        readMatches();
        setAverage();


        int i;


        for (i = 0; i < league.numberofTeams; i++)
        {
                for (int j = 1; j < league.numberofTeams - i; j++)
                {
                        if (teams[j - 1].pts < teams[j].pts)
                        {
                                temp = teams[j - 1];
                                teams[j - 1] = teams[j];
                                teams[j] = temp;


                        }
                        else if (teams[j - 1].pts == teams[j].pts && teams[j - 1].average > teams[j].average)
                        {
                                temp = teams[j - 1];
                                teams[j - 1] = teams[j];
                                teams[j] = temp;
                        }
                }


        }


        puts("****************************Türkiye Futbol Ligi*************************************");
        puts("*      Takim          Kisa Ismi       OM     G     B     M     AG    YG    A     P *");


        for (int i = 0; i < league.numberofTeams; i++)
        {
                printf("* %2d->%12s%10c%12d%6d%6d%6d%6d%6d%6d%6d *\n", i + 1, teams[i].name, teams[i].shortName, teams[i].playedMatch, teams[i].win, teams[i].draw, teams[i].loss, teams[i].goalsFor, teams[i].goalsAgainst, teams[i].goalsFor - teams[i].goalsAgainst, teams[i].pts);
        }
        puts("************************************************************************************");
}


void menu()
{


        int menuSelection;




        puts("[1]Ayarlari degistirmek icin ");
        puts("[2]Takim eklemek icin");
        puts("[3]Mac eklemek icin ");
        puts("[4]Degisim yapmadan lig tablosunu gormek icin");


        printf("\nYapmak istediginiz islemi seciniz:");
        scanf("%d", &menuSelection);


        system("CLS");




        if (menuSelection < 1 || menuSelection>4)
        {
                printf("Gecersiz giris yaptiniz.\n");


        }
        else
        {
                switch (menuSelection)
                {
                case 1:
                        changeSettings();
                        break;
                case 2:
                        addTeamwthKeyboard();
                        break;
                case 3:
                        addMatchwthKeyboard();
                        break;
                case 4:
                        leagueTable();
                        break;
                default:
                        break;
                }


        }




}