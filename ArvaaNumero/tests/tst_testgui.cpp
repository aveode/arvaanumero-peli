#include <QtTest>
#include <QCoreApplication>
#include <QRegularExpression>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>

#include "mainwindow.h"

// add necessary includes here

class TestGUI : public QObject
{
    Q_OBJECT

public:
    TestGUI();
    ~TestGUI();

private slots:
    void testElements();
    void testGuessCounter();
    void testGuessNumberCorrect();
    void testGameOver();
    void testTooSmall();
    void testTooBig();
    void testRestart();
};

TestGUI::TestGUI()
{

}

TestGUI::~TestGUI()
{

}



void TestGUI::testElements()
{
    MainWindow window;
    window.show();

    QPushButton *guessButton = window.findChild<QPushButton*>("pushButton");
    QVERIFY2(guessButton != nullptr, "guessButton does now exist");

    QLabel *labelMessage = window.findChild<QLabel*>("labelCounter");
    QVERIFY2(labelMessage != nullptr, "label counter does now exist");

    QLabel *labelStatus = window.findChild<QLabel*>("labelStatus");
    QVERIFY2(labelStatus != nullptr, "label counter does now exist");

    // findChild returns a pointer to the first child widget with the given name
    // It returns nullptr if such a widget can not be found
    QTextEdit *guessInput = window.findChild<QTextEdit*>("textGuess");
    QVERIFY2(guessInput != nullptr, "LineEdit does now exist");

    QTest::qWait(100);
}


void TestGUI::testGuessCounter() {
    MainWindow window;
    window.show();

    // findChild returns a pointer to the first child widget with the given name
    // It returns nullptr if such a widget can not be found
    QLabel *messageLabel = window.findChild<QLabel*>("labelCounter");
    QPushButton *guessButton = window.findChild<QPushButton*>("pushButton");


    for (int i = 10; i > 0; i--) {
        QString sLabel = messageLabel->text();
        QString pattern = QString("^.*%1.*$").arg(i);

        QRegularExpression regex(pattern);
        //regex.setPatternOptions(QRegularExpression::MultilineOption | QRegularExpression::DotMatchesEverythingOption);

        QRegularExpressionMatch match = regex.match(sLabel);

        // Verify the output
        QVERIFY2(match.hasMatch(), pattern.toUtf8());

        QTest::mouseClick(guessButton, Qt::LeftButton);
        QTest::qWait(100);
    }
}


void TestGUI::testGuessNumberCorrect()
{
    MainWindow window;
    window.show();

    QPushButton *guessButton = window.findChild<QPushButton*>("pushButton");
    QLabel *messageLabel = window.findChild<QLabel*>("labelCounter");
    QLabel *responseLabel = window.findChild<QLabel*>("labelStatus");
    QTextEdit *guessInput = window.findChild<QTextEdit*>("textGuess");

    int guess = 50;
    int low = 0;
    int high = 100;
    int i = 0;
    for (i = 0; i < 10; i++) {
        guess = 0.5*(low+high);
        // Make sure the widgets are not nullptr before using them
        if (guessInput && guessButton && messageLabel) {
            guessInput->setPlainText("");
            QTest::keyClicks(guessInput, QString::number(guess));
            QTest::mouseClick(guessButton, Qt::LeftButton);

            QString response = responseLabel->text();
            if (response.contains("Oikein")) {
                break;
            }
            if (response.contains("enemmän")) {
                low = guess + 1;
            } else {
                high = guess - 1;
            }

            //QCOMPARE(messageLabel->text(), QString("Correct guess!"));
            QTest::qWait(100);
        }
    }

    QVERIFY2(i <= 10, "Correct number not found in 10 tries");
}


void TestGUI::testGameOver()
{
    MainWindow window;
    window.show();

    QPushButton *guessButton = window.findChild<QPushButton*>("pushButton");
    QLabel *messageLabel = window.findChild<QLabel*>("labelCounter");
    QLabel *responseLabel = window.findChild<QLabel*>("labelStatus");
    QTextEdit *guessInput = window.findChild<QTextEdit*>("textGuess");

    int guess = 150;
    QString response;
    for (int i = 0; i < 10; i++) {
        // Make sure the widgets are not nullptr before using them
        if (guessInput && guessButton && messageLabel) {
            guessInput->setPlainText("");
            QTest::keyClicks(guessInput, QString::number(guess));
            QTest::mouseClick(guessButton, Qt::LeftButton);

            response = responseLabel->text();
            QVERIFY(response.contains("Oikein") == false);

            QTest::qWait(100);
        }
    }

    QVERIFY(response.contains("Game over"));
}


void TestGUI::testTooSmall()
{
    MainWindow window;
    window.show();

    QPushButton *guessButton = window.findChild<QPushButton*>("pushButton");
    QLabel *messageLabel = window.findChild<QLabel*>("labelCounter");
    QLabel *responseLabel = window.findChild<QLabel*>("labelStatus");
    QTextEdit *guessInput = window.findChild<QTextEdit*>("textGuess");

    int guess = -150;

    // Make sure the widgets are not nullptr before using them
    if (guessInput && guessButton && messageLabel) {
        guessInput->setPlainText("");
        QTest::keyClicks(guessInput, QString::number(guess));
        QTest::mouseClick(guessButton, Qt::LeftButton);

        QTest::qWait(1000);
        QString response = responseLabel->text();
        QVERIFY(response.contains("enemmän"));
    } else {
        QVERIFY(false);
    }

}


void TestGUI::testTooBig()
{
    MainWindow window;
    window.show();

    QPushButton *guessButton = window.findChild<QPushButton*>("pushButton");
    QLabel *messageLabel = window.findChild<QLabel*>("labelCounter");
    QLabel *responseLabel = window.findChild<QLabel*>("labelStatus");
    QTextEdit *guessInput = window.findChild<QTextEdit*>("textGuess");

    int guess = 150;

    // Make sure the widgets are not nullptr before using them
    if (guessInput && guessButton && messageLabel) {
        guessInput->setPlainText("");
        QTest::keyClicks(guessInput, QString::number(guess));
        QTest::mouseClick(guessButton, Qt::LeftButton);

        QTest::qWait(1000);
        QString response = responseLabel->text();
        QVERIFY(response.contains("vähemmän"));
    } else {
        QVERIFY(false);
    }

}


void TestGUI::testRestart()
{
    MainWindow window;
    window.show();

    QPushButton *guessButton = window.findChild<QPushButton*>("pushButton");
    QLabel *messageLabel = window.findChild<QLabel*>("labelCounter");
    QLabel *responseLabel = window.findChild<QLabel*>("labelStatus");
    QTextEdit *guessInput = window.findChild<QTextEdit*>("textGuess");

    int correct1, correct2;

    {
        int guess = 50;
        int low = 0;
        int high = 100;
        int i = 0;
        for (i = 0; i < 10; i++) {
            guess = 0.5*(low+high);
            // Make sure the widgets are not nullptr before using them
            if (guessInput && guessButton && messageLabel) {
                guessInput->setPlainText("");
                QTest::keyClicks(guessInput, QString::number(guess));
                QTest::mouseClick(guessButton, Qt::LeftButton);

                QString response = responseLabel->text();
                if (response.contains("Oikein")) {
                    correct1 = guess;
                    break;
                }
                if (response.contains("enemmän")) {
                    low = guess + 1;
                } else {
                    high = guess - 1;
                }

                //QCOMPARE(messageLabel->text(), QString("Correct guess!"));
                QTest::qWait(100);
            }
        }

        QVERIFY2(i <= 10, "Correct number not found in 10 tries");
    }
    {
        int guess = 50;
        int low = 0;
        int high = 100;
        int i = 0;
        for (i = 0; i < 10; i++) {
            guess = 0.5*(low+high);
            // Make sure the widgets are not nullptr before using them
            if (guessInput && guessButton && messageLabel) {
                guessInput->setPlainText("");
                QTest::keyClicks(guessInput, QString::number(guess));
                QTest::mouseClick(guessButton, Qt::LeftButton);

                QString response = responseLabel->text();
                if (response.contains("Oikein")) {
                    correct2 = guess;
                    break;
                }
                if (response.contains("enemmän")) {
                    low = guess + 1;
                } else {
                    high = guess - 1;
                }

                //QCOMPARE(messageLabel->text(), QString("Correct guess!"));
                QTest::qWait(100);
            }
        }

        QVERIFY2(i <= 10, "Correct number not found in 10 tries");
    }

    QVERIFY2(correct1 != correct2, "After restart there should be another number");
}





QTEST_MAIN(TestGUI)

#include "tst_testgui.moc"
