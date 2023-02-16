pipeline {
    agent any

    stages {
        stage('Build') {
            steps {
                sh '''
			make clean all CFG=../fun_dclib/cfg/durango16k.cfg DCLIB=../fun_dclib/bin DCINC=../fun_dclib/inc RESCOMP=../fun_rescomp/target/rescomp.jar
                '''
            }
        }
        stage('Deploy') {
            steps {
            	sh '''
			echo 'Deploy...'
            		scp $WORKSPACE/witch.dux jenkins@aquila.emiliollbb.net:/var/www/html/roms/witch.dux
            		scp $WORKSPACE/witch.dux jenkins@piscis.emiliollbb.net:/var/www/html/roms/witch.dux
            		scp $WORKSPACE/witch.dux jenkins@aries.emiliollbb.net:/var/www/roms/witch.dux
            	'''
            }
        }
        
    }
}

