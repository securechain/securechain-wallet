#include "uritests.h"

#include "guiutil.h"
#include "walletmodel.h"

#include <QUrl>

void URITests::uriTests()
{
    SendCoinsRecipient rv;
    QUrl uri;
    uri.setUrl(QString("securecoin:sJvj1ttPXcAHB71TAqVFm36Vx88PMhmpYq?req-dontexist="));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("securecoin:sJvj1ttPXcAHB71TAqVFm36Vx88PMhmpYq?dontexist="));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("sJvj1ttPXcAHB71TAqVFm36Vx88PMhmpYq"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("securecoin:sJvj1ttPXcAHB71TAqVFm36Vx88PMhmpYq?label=Wikipedia Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("sJvj1ttPXcAHB71TAqVFm36Vx88PMhmpYq"));
    QVERIFY(rv.label == QString("Wikipedia Example Address"));
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("securecoin:sJvj1ttPXcAHB71TAqVFm36Vx88PMhmpYq?amount=0.001"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("sJvj1ttPXcAHB71TAqVFm36Vx88PMhmpYq"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100);

    uri.setUrl(QString("securecoin:sJvj1ttPXcAHB71TAqVFm36Vx88PMhmpYq?amount=1.001"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("sJvj1ttPXcAHB71TAqVFm36Vx88PMhmpYq"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100100);

    uri.setUrl(QString("securecoin:sJvj1ttPXcAHB71TAqVFm36Vx88PMhmpYq?amount=100&label=Wikipedia Example"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("sJvj1ttPXcAHB71TAqVFm36Vx88PMhmpYq"));
    QVERIFY(rv.amount == 10000000LL);
    QVERIFY(rv.label == QString("Wikipedia Example"));

    uri.setUrl(QString("securecoin:sJvj1ttPXcAHB71TAqVFm36Vx88PMhmpYq?message=Wikipedia Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("sJvj1ttPXcAHB71TAqVFm36Vx88PMhmpYq"));
    QVERIFY(rv.label == QString());

    QVERIFY(GUIUtil::parseBitcoinURI("securecoin://sJvj1ttPXcAHB71TAqVFm36Vx88PMhmpYq?message=Wikipedia Example Address", &rv));
    QVERIFY(rv.address == QString("sJvj1ttPXcAHB71TAqVFm36Vx88PMhmpYq"));
    QVERIFY(rv.label == QString());

    uri.setUrl(QString("securecoin:sJvj1ttPXcAHB71TAqVFm36Vx88PMhmpYq?req-message=Wikipedia Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("securecoin:sJvj1ttPXcAHB71TAqVFm36Vx88PMhmpYq?amount=1,000&label=Wikipedia Example"));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("securecoin:sJvj1ttPXcAHB71TAqVFm36Vx88PMhmpYq?amount=1,000.0&label=Wikipedia Example"));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));
}
