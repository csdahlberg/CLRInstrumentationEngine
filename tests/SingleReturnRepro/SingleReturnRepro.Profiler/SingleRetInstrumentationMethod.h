#pragma once
#include <atlcomcli.h>
#include "..\..\..\src\InstrumentationEngine.Api\InstrumentationEngine.h"

namespace SingleRetRepro
{
    namespace Profiler
    {
        class
            __declspec(uuid("3CA7144B-0FC3-4437-BDAD-8275760C2D44"))
            SingleRetInstrumentationMethod : public IInstrumentationMethod
        {
        private:
            ULONG m_refCount;
        public:

            SingleRetInstrumentationMethod();

            // Inherited via IInstrumentationMethod
            virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppvObject) override;
            virtual ULONG __stdcall AddRef(void) override;
            virtual ULONG __stdcall Release(void) override;
            virtual HRESULT __stdcall Initialize(IProfilerManager* pProfilerManager) override;
            virtual HRESULT __stdcall OnAppDomainCreated(IAppDomainInfo* pAppDomainInfo) override;
            virtual HRESULT __stdcall OnAppDomainShutdown(IAppDomainInfo* pAppDomainInfo) override;
            virtual HRESULT __stdcall OnAssemblyLoaded(IAssemblyInfo* pAssemblyInfo) override;
            virtual HRESULT __stdcall OnAssemblyUnloaded(IAssemblyInfo* pAssemblyInfo) override;
            virtual HRESULT __stdcall OnModuleLoaded(IModuleInfo* pModuleInfo) override;
            virtual HRESULT __stdcall OnModuleUnloaded(IModuleInfo* pModuleInfo) override;
            virtual HRESULT __stdcall OnShutdown(void) override;
            virtual HRESULT __stdcall ShouldInstrumentMethod(IMethodInfo* pMethodInfo, BOOL isRejit, BOOL* pbInstrument) override;
            virtual HRESULT __stdcall BeforeInstrumentMethod(IMethodInfo* pMethodInfo, BOOL isRejit) override;
            virtual HRESULT __stdcall InstrumentMethod(IMethodInfo* pMethodInfo, BOOL isRejit) override;
            virtual HRESULT __stdcall OnInstrumentationComplete(IMethodInfo* pMethodInfo, BOOL isRejit) override;
            virtual HRESULT __stdcall AllowInlineSite(IMethodInfo* pMethodInfoInlinee, IMethodInfo* pMethodInfoCaller, BOOL* pbAllowInline) override;
        };
    }
}