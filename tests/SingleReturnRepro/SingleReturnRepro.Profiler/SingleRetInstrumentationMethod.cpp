#include "pch.h"
#include "SingleRetInstrumentationMethod.h"
#include <fstream>

using namespace SingleRetRepro::Profiler;

void writelog(std::string msg)
{
    std::ofstream outfile;
    outfile.open("log.txt", std::ios_base::app);
    outfile << msg << std::endl;
}

SingleRetInstrumentationMethod::SingleRetInstrumentationMethod()
    : m_refCount(0)
{
    writelog("SingleRetInstrumentationMethod::SingleRetInstrumentationMethod");
}

HRESULT __stdcall SingleRetInstrumentationMethod::QueryInterface(REFIID riid, void** ppvObject)
{
    if (riid == __uuidof(SingleRetInstrumentationMethod)
        || riid == IID_IUnknown)
    {
        AddRef();
        *ppvObject = this;
        return S_OK;
    }

    return E_NOINTERFACE;
}

ULONG __stdcall SingleRetInstrumentationMethod::AddRef(void)
{
    return InterlockedIncrement(&m_refCount);
}

ULONG __stdcall SingleRetInstrumentationMethod::Release(void)
{
    ULONG refCount = InterlockedDecrement(&m_refCount);

    if (refCount == 0)
    {
        delete this;
    }

    return refCount;
}

HRESULT __stdcall SingleRetInstrumentationMethod::Initialize(IProfilerManager* pProfilerManager)
{
    return S_OK;
}

HRESULT __stdcall SingleRetInstrumentationMethod::OnAppDomainCreated(IAppDomainInfo* pAppDomainInfo)
{
    return S_OK;
}

HRESULT __stdcall SingleRetInstrumentationMethod::OnAppDomainShutdown(IAppDomainInfo* pAppDomainInfo)
{
    return S_OK;
}

HRESULT __stdcall SingleRetInstrumentationMethod::OnAssemblyLoaded(IAssemblyInfo* pAssemblyInfo)
{
    return S_OK;
}

HRESULT __stdcall SingleRetInstrumentationMethod::OnAssemblyUnloaded(IAssemblyInfo* pAssemblyInfo)
{
    return S_OK;
}

HRESULT __stdcall SingleRetInstrumentationMethod::OnModuleLoaded(IModuleInfo* pModuleInfo)
{
    return S_OK;
}

HRESULT __stdcall SingleRetInstrumentationMethod::OnModuleUnloaded(IModuleInfo* pModuleInfo)
{
    return S_OK;
}

HRESULT __stdcall SingleRetInstrumentationMethod::OnShutdown(void)
{
    return S_OK;
}

HRESULT __stdcall SingleRetInstrumentationMethod::ShouldInstrumentMethod(IMethodInfo* pMethodInfo, BOOL isRejit, BOOL* pbInstrument)
{
    CComPtr<IType> pDeclaringType;
    pMethodInfo->GetDeclaringType(&pDeclaringType);

    CComBSTR pTypeName;
    pDeclaringType->GetName(&pTypeName);

    if (pTypeName == "String")
    {
        CComBSTR pMethodName;
        pMethodInfo->GetName(&pMethodName);

        *pbInstrument = pMethodName == L"Concat" ? TRUE : FALSE;
    }

    return S_OK;
}

HRESULT __stdcall SingleRetInstrumentationMethod::BeforeInstrumentMethod(IMethodInfo* pMethodInfo, BOOL isRejit)
{
    return S_OK;
}

HRESULT __stdcall SingleRetInstrumentationMethod::InstrumentMethod(IMethodInfo* pMethodInfo, BOOL isRejit)
{
    CComPtr<IInstructionFactory> pInstructionFactory;
    pMethodInfo->GetInstructionFactory(&pInstructionFactory);

    CComPtr<IInstructionGraph> pInstructionGraph;
    pMethodInfo->GetInstructions(&pInstructionGraph);

    CComPtr<ISingleRetDefaultInstrumentation> pSingleRet;
    pMethodInfo->GetSingleRetDefaultInstrumentation(&pSingleRet);
    pSingleRet->Initialize(pInstructionGraph);
    pSingleRet->ApplySingleRetDefaultInstrumentation();

    CComPtr<IInstruction> pFirstInstruction;
    pInstructionGraph->GetFirstInstruction(&pFirstInstruction);

    CComPtr<IInstruction> pNopInstr;
    pInstructionFactory->CreateInstruction(Cee_Nop, &pNopInstr);
    pInstructionGraph->InsertBefore(pFirstInstruction, pNopInstr);

    return S_OK;
}

HRESULT __stdcall SingleRetInstrumentationMethod::OnInstrumentationComplete(IMethodInfo* pMethodInfo, BOOL isRejit)
{
    return S_OK;
}

HRESULT __stdcall SingleRetInstrumentationMethod::AllowInlineSite(IMethodInfo* pMethodInfoInlinee, IMethodInfo* pMethodInfoCaller, BOOL* pbAllowInline)
{
    return S_OK;
}
