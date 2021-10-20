// This file is generated by omniidl (C++ backend) - omniORB_4_2. Do not edit.

#include "log_parser.hh"

OMNI_USING_NAMESPACE(omni)

static const char* _0RL_dyn_library_version = omniORB_4_2_dyn;

static ::CORBA::TypeCode::_Tracker _0RL_tcTrack(__FILE__);

static CORBA::TypeCode_ptr _0RL_tc_logseq = CORBA::TypeCode::PR_alias_tc("IDL:logseq:1.0", "logseq", CORBA::TypeCode::PR_sequence_tc(0, CORBA::TypeCode::PR_string_tc(0, &_0RL_tcTrack), &_0RL_tcTrack), &_0RL_tcTrack);


const CORBA::TypeCode_ptr _tc_logseq = _0RL_tc_logseq;

const CORBA::TypeCode_ptr _tc_Log_Parser = CORBA::TypeCode::PR_interface_tc("IDL:Log_Parser:1.0", "Log_Parser", &_0RL_tcTrack);

static void _0RL_logseq_marshal_fn(cdrStream& _s, void* _v)
{
  logseq* _p = (logseq*)_v;
  *_p >>= _s;
}
static void _0RL_logseq_unmarshal_fn(cdrStream& _s, void*& _v)
{
  logseq* _p = new logseq;
  *_p <<= _s;
  _v = _p;
}
static void _0RL_logseq_destructor_fn(void* _v)
{
  logseq* _p = (logseq*)_v;
  delete _p;
}

void operator<<=(::CORBA::Any& _a, const logseq& _s)
{
  logseq* _p = new logseq(_s);
  _a.PR_insert(_0RL_tc_logseq,
               _0RL_logseq_marshal_fn,
               _0RL_logseq_destructor_fn,
               _p);
}
void operator<<=(::CORBA::Any& _a, logseq* _sp)
{
  _a.PR_insert(_0RL_tc_logseq,
               _0RL_logseq_marshal_fn,
               _0RL_logseq_destructor_fn,
               _sp);
}

::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, logseq*& _sp)
{
  return _a >>= (const logseq*&) _sp;
}
::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, const logseq*& _sp)
{
  void* _v;
  if (_a.PR_extract(_0RL_tc_logseq,
                    _0RL_logseq_unmarshal_fn,
                    _0RL_logseq_marshal_fn,
                    _0RL_logseq_destructor_fn,
                    _v)) {
    _sp = (const logseq*)_v;
    return 1;
  }
  return 0;
}

static void _0RL_Log__Parser_marshal_fn(cdrStream& _s, void* _v)
{
  omniObjRef* _o = (omniObjRef*)_v;
  omniObjRef::_marshal(_o, _s);
}
static void _0RL_Log__Parser_unmarshal_fn(cdrStream& _s, void*& _v)
{
  omniObjRef* _o = omniObjRef::_unMarshal(Log_Parser::_PD_repoId, _s);
  _v = _o;
}
static void _0RL_Log__Parser_destructor_fn(void* _v)
{
  omniObjRef* _o = (omniObjRef*)_v;
  if (_o)
    omni::releaseObjRef(_o);
}

void operator<<=(::CORBA::Any& _a, Log_Parser_ptr _o)
{
  Log_Parser_ptr _no = Log_Parser::_duplicate(_o);
  _a.PR_insert(_tc_Log_Parser,
               _0RL_Log__Parser_marshal_fn,
               _0RL_Log__Parser_destructor_fn,
               _no->_PR_getobj());
}
void operator<<=(::CORBA::Any& _a, Log_Parser_ptr* _op)
{
  _a.PR_insert(_tc_Log_Parser,
               _0RL_Log__Parser_marshal_fn,
               _0RL_Log__Parser_destructor_fn,
               (*_op)->_PR_getobj());
  *_op = Log_Parser::_nil();
}

::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, Log_Parser_ptr& _o)
{
  void* _v;
  if (_a.PR_extract(_tc_Log_Parser,
                    _0RL_Log__Parser_unmarshal_fn,
                    _0RL_Log__Parser_marshal_fn,
                    _0RL_Log__Parser_destructor_fn,
                    _v)) {
    omniObjRef* _r = (omniObjRef*)_v;
    if (_r)
      _o = (Log_Parser_ptr)_r->_ptrToObjRef(Log_Parser::_PD_repoId);
    else
      _o = Log_Parser::_nil();
    return 1;
  }
  return 0;
}
