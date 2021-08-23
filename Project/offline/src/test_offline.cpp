
#include "../include/GlobalDefine.hpp"
#include "../include/Configuration.hpp"
#include "../include/DirScanner.hpp"
#include "../include/PageLib.hpp"
#include "../include/WordSegmentation.hpp"
#include "../include/WebPage.hpp"
#include "../include/PageLibPreprocessor.hpp"

#include <stdio.h>
#include <time.h>

int main(void)
{
	wd::Configuration conf("conf/my.conf");
	conf.debug();

	wd::DirScanner dirScanner(conf);
	dirScanner();
	dirScanner.debug();

	wd::PageLib pagelib(conf, dirScanner);

	time_t t1 = time(NULL);
	pagelib.create();
	pagelib.store();
	time_t t2 = time(NULL);
	printf("raw lib create and store time: %ld min\n", (t2 - t1));

	wd::PageLibPreprocessor libPreprocessor(conf);
	libPreprocessor.doProcess();

	return 0;
}
