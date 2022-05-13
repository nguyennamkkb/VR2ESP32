#include "fs01_cmd.h"

fs01_cmd::fs01_cmd()
{

}
QString fs01_cmd::enumToString(qint16 cmd)
{   int index = metaObject()->indexOfEnumerator("fs01_code");
    QMetaEnum metaEnum = metaObject()->enumerator(index);
    return metaEnum.valueToKey(cmd);
}
