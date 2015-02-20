//
//  Test.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/02/20.
//
//

#ifndef __BabylonClicker__Test__
#define __BabylonClicker__Test__

#include "littlePony.h"

class Test : public Ref {
public:
    Test();
    virtual ~Test();
    virtual bool init();
    CREATE_FUNC(Test);
    bool go();
};

#endif /* defined(__BabylonClicker__Test__) */
