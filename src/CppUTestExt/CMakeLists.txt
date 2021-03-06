set(CppUTestExt_src
        CodeMemoryReportFormatter.cpp
        IEEE754ExceptionsPlugin.cpp
        MemoryReporterPlugin.cpp
        MockFailure.cpp
        MockSupportPlugin.cpp
        MockActualCall.cpp
        MockSupport_c.cpp
        MemoryReportAllocator.cpp
        MockExpectedCall.cpp
        MockNamedValue.cpp
        OrderedTest.cpp
        MemoryReportFormatter.cpp
        MockExpectedCallsList.cpp
        MockSupport.cpp
        TestDouble.cpp
        TestDoubleParameter.cpp
        ActualCall.cpp
)

set(CppUTestExt_headers
        ${CppUTestRootDirectory}/include/CppUTestExt/CodeMemoryReportFormatter.h
        ${CppUTestRootDirectory}/include/CppUTestExt/IEEE754ExceptionsPlugin.h
        ${CppUTestRootDirectory}/include/CppUTestExt/MemoryReportAllocator.h
        ${CppUTestRootDirectory}/include/CppUTestExt/MockExpectedCall.h
        ${CppUTestRootDirectory}/include/CppUTestExt/MockCheckedExpectedCall.h
        ${CppUTestRootDirectory}/include/CppUTestExt/MockExpectedCallsList.h
        ${CppUTestRootDirectory}/include/CppUTestExt/MockSupportPlugin.h
        ${CppUTestRootDirectory}/include/CppUTestExt/MemoryReportFormatter.h
        ${CppUTestRootDirectory}/include/CppUTestExt/MockFailure.h
        ${CppUTestRootDirectory}/include/CppUTestExt/MockSupport.h
        ${CppUTestRootDirectory}/include/CppUTestExt/MockSupport_c.h
        ${CppUTestRootDirectory}/include/CppUTestExt/GMock.h
        ${CppUTestRootDirectory}/include/CppUTestExt/GTest.h
        ${CppUTestRootDirectory}/include/CppUTestExt/MemoryReporterPlugin.h
        ${CppUTestRootDirectory}/include/CppUTestExt/OrderedTest.h
        ${CppUTestRootDirectory}/include/CppUTestExt/GTestConvertor.h
        ${CppUTestRootDirectory}/include/CppUTestExt/MockActualCall.h
        ${CppUTestRootDirectory}/include/CppUTestExt/MockCheckedActualCall.h
        ${CppUTestRootDirectory}/include/CppUTestExt/MockNamedValue.h
        ${CppUTestRootDirectory}/include/CppUTestExt/MockSupport.h
        ${CppUTestRootDirectory}/include/CppUTestExt/TestDouble.h
        ${CppUTestRootDirectory}/include/CppUTestExt/TestDoubleParameter.h
        ${CppUTestRootDirectory}/include/CppUTestExt/ExpectCall.h
        ${CppUTestRootDirectory}/include/CppUTestExt/ActualCall.h
)

add_library(CppUTestExt STATIC ${CppUTestExt_src} ${CppUTestExt_headers})
target_link_libraries(CppUTestExt ${CPPUNIT_EXTERNAL_LIBRARIES})
install(FILES ${CppUTestExt_headers} DESTINATION include/CppUTestExt)
install(TARGETS CppUTestExt
    EXPORT CppUTestTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
