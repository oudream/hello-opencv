#include "Python.h"

#include <stdio.h>
#include <stdlib.h>

#define sContextLen 1024*64
char sContext[sContextLen];

int loadPyfile (char * pFileName) {
    FILE * pFile;
    long lSize;
    char * buffer;
    size_t result;

    pFile = fopen ( pFileName , "rb" );
    if (pFile==NULL) {fputs ("File error",stderr); exit (1);}

    // obtain file size:
    fseek (pFile , 0 , SEEK_END);
    lSize = ftell (pFile);
    rewind (pFile);

    // allocate memory to contain the whole file:
    buffer = (char*) malloc (sizeof(char)*lSize);
    if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

    // copy the file into the buffer:
    result = fread (buffer,1,lSize,pFile);
    if (result != lSize) {fputs ("Reading error",stderr); exit (3);}

    if (sContextLen<lSize) {fputs ("Context tool small, error",stderr); exit (3);}
    memcpy(sContext, buffer, lSize);
    sContext[lSize] = 0;

    /* the whole file is now loaded in the memory buffer. */

    // terminate
    fclose (pFile);
    free (buffer);
    return 0;
}

int main()
{
    Py_Initialize();

    printf("i am in c++, step 0 getpid()=%u", getpid());

    setenv("myenv", "abc1", 1);

    PyRun_SimpleString("print('hello');");

    PyRun_SimpleString("import os\n\nprint('step 1: ')\nprint(os.getenv('myenv'));");
    PyRun_SimpleString("import os\n\nprint('step 2: ')\nos.environ['myenv'] = 'abc2';");
    PyRun_SimpleString("import os\n\nprint('step 3: ')\nprint(os.getenv('myenv'));");

    char sFilePath[] = "/opt/limi/hello-opencv/hello/python/callpython3/a.py";

    if (loadPyfile(sFilePath) != 0)
    {
        PyRun_SimpleString("print('load file fail!');");
        return (1);
    }


    char buffer [512];
    sprintf (buffer, "print('load python script (%s) now :');", sFilePath);

    PyRun_SimpleString(buffer);

    PyRun_SimpleString(sContext);

    Py_Finalize();
    return 0;
}

//// * env
//    hello
//        step 1:
//    None
//        step 2:
//    step 3:
//    abc2
//        load python script (/opt/limi/hello-opencv/hello/python/callpython3/a.py) now :
//    environ({'PATH': '/opt/fff/anaconda3/bin:/opt/fff/anaconda3/condabin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/Applications/VMware Fusion.app/Contents/Public:/Library/TeX/texbin:/usr/local/go/bin:/usr/local/share/dotnet:/opt/X11/bin:~/.dotnet/tools:/Library/Frameworks/Mono.framework/Versions/Current/Commands:/Applications/Wireshark.app/Contents/MacOS:/Applications/Postgres.app/Contents/Versions/latest/bin:/opt/fff/apache-maven-3.6.3/bin:/usr/local/hadoop/bin:/usr/local/go/bin:/usr/local/mysql/bin:/ddd/cshell/tools/oudream:/Users/oudream/Library/Android/sdk/platform-tools:/Users/oudream/bin:/opt/local/bin:/opt/local/sbin', 'CONDA_DEFAULT_ENV': 'base', 'CONDA_EXE': '/opt/fff/anaconda3/bin/conda', 'JAVA_HOME': '/Library/Java/JavaVirtualMachines/jdk1.8.0_151.jdk/Contents/Home', 'CONDA_PYTHON_EXE': '/opt/fff/anaconda3/bin/python', 'ANDROID_HOME': '/Users/oudream/Library/Android/sdk', 'COMMAND_MODE': 'unix2003', 'PS1': '(base) \\[\\033[01;32m\\]\\u@\\h\\[\\033[00m\\]:\\[\\033[01;36m\\]\\w\\[\\033[00m\\]\\$', 'JRE_HOME': '/Library/Java/JavaVirtualMachines/jdk1.8.0_151.jdk/Contents/Home/jre', 'CONDA_PREFIX': '/opt/fff/anaconda3', 'DISPLAY': '/private/tmp/com.apple.launchd.oCL6p4JCrB/org.macosforge.xquartz:0', 'MAVEN_HOME': '/opt/fff/apache-maven-3.6.3', '_CE_M': '', 'LOGNAME': 'oudream', 'XPC_SERVICE_NAME': 'com.apple.xpc.launchd.oneshot.0x10000001.clion', 'PWD': '/opt/limi/hello-opencv/build/deploy/unix/bin_d', 'BASH_SILENCE_DEPRECATION_WARNING': '1', 'CONDA_SHLVL': '1', 'NODE_PATH': '/usr/local/lib/node_modules:', 'PYTHONPATH': '/ddd/cpy/cpy:', 'SHELL': '/bin/bash', 'LSCOLORS': 'gxfxcxdxbxegedabagacad', 'GOPATH': '/opt/fff/gopath', 'SECURITYSESSIONID': '186a6', 'CLICOLOR': '1', 'USER': 'oudream', 'GOROOT': '/usr/local/go', 'CLASSPATH': '/usr/local/hadoop/etc/hadoop:/usr/local/hadoop/share/hadoop/common/lib/*:/usr/local/hadoop/share/hadoop/common/*:/usr/local/hadoop/share/hadoop/hdfs:/usr/local/hadoop/share/hadoop/hdfs/lib/*:/usr/local/hadoop/share/hadoop/hdfs/*:/usr/local/hadoop/share/hadoop/yarn/lib/*:/usr/local/hadoop/share/hadoop/yarn/*:/usr/local/hadoop/share/hadoop/mapreduce/lib/*:/usr/local/hadoop/share/hadoop/mapreduce/*:/usr/local/hadoop/contrib/capacity-scheduler/*.jar', 'TMPDIR': '/var/folders/jn/gdrdjh8n6vz8sjv79bwj084h0000gn/T/', 'LaunchInstanceID': '27402B11-500D-4E8E-A712-E41DBD2ECC57', 'SSH_AUTH_SOCK': '/private/tmp/com.apple.launchd.pEfvm6yWZr/Listeners', '_CE_CONDA': '', 'XPC_FLAGS': '0x0', 'NSUnbufferedIO': 'YES', 'HADOOP_HOME': '/usr/local/hadoop', '__CF_USER_TEXT_ENCODING': '0x1F5:0x19:0x34', 'CONDA_PROMPT_MODIFIER': '(base) ', 'LC_CTYPE': 'UTF-8', 'HOME': '/Users/oudream', 'myenv': 'abc2'})

