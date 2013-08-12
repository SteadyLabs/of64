#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"

#include "Poco/Net/HTTPSClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPStreamFactory.h"
#include "Poco/Net/HTTPMessage.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPBasicCredentials.h"
#include "Poco/Net/Context.h"
#include "Poco/StreamCopier.h"
#include "Poco/Exception.h"
#include "Poco/URI.h"


using Poco::Net::HTTPStreamFactory;
using Poco::Net::Context;
using Poco::Net::HTTPSClientSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPMessage;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPBasicCredentials;
using Poco::StreamCopier;
using Poco::Exception;
using Poco::URI;

using namespace std;


//========================================================================
int main( ){
    
    try
    {
        cout << "try" << endl;
        URI uri("https://api.parse.com/1/login/?username={USERNAME}&password={PASSWORD}");
        std::string path(uri.getPathAndQuery());
        if (path.empty()) path = "/";
        
        const Poco::Net::Context::Ptr context( new Poco::Net::Context( Poco::Net::Context::CLIENT_USE, "", "", "", Poco::Net::Context::VERIFY_NONE) );
        
        HTTPSClientSession session(uri.getHost(), uri.getPort(), context);
        HTTPRequest req(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
        
        req.add("X-Parse-Application-Id", "{PARSE-APP-ID}");
        req.add("X-Parse-REST-API-Key", "{PARSE-REST-API-Key}");
        req.setContentType("application/json");
        req.setKeepAlive(false);
       
       
        //  If requirint HTTP Basic Credential.
        //Poco::Net::HTTPBasicCredentials cred("user", "pass");
        // cred.authenticate(req);
        
        req.write(cout);
        
        session.sendRequest(req);
        HTTPResponse res;
        istream& rs = session.receiveResponse(res);
        
        string result;
        StreamCopier::copyToString(rs, result);
        
        cout << result << endl;
    }
    catch (Exception& exc)
    {
        std::cerr << exc.displayText() << std::endl;
        cout << "fail" << endl;
    }
    


    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1024,768, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new testApp());
    
    
        

    

}
