      SUBROUTINE DLLBODY (RO)
      REAL, INTENT(OUT) :: RO

      INTEGER, SAVE :: COUNT

      WRITE (6,'(20(A,/))')  &
        'DLLBODY lignel           .',&
        'DLLBODY ligne2           .',&
        'DLLBODY ligne3           .'

      COUNT = COUNT + 1
      RO = COUNT
      
      END SUBROUTINE DLLBODY

