clear;

% definition of the stochastic block model

% number vertices
n = 200;%200
n_str = int2str(n);

% number of communities
q = 2;%2
q_str = int2str(q);

pinValueVector = [0.3;0.6;0.9;]; % normal case
% pinValueVector = [0.001;0.01;0.1;0.5;0.9]; % sparse case
noColumnsInPlot = 2;

for pinValueNo=1:max(size(pinValueVector))
    
    % probability matrix indicating the proability of edge between communities
    pout = 0;
    pin = pinValueVector(pinValueNo,1);
    pin_str = num2str(pin);
    cin = floor(pin*n);
    cout = floor(pout*n);
    % let number of iterations be proportional to number of vertices in
    % graph
    maxNoIterations = 100;
    deltaCout = (cin - cout) / maxNoIterations;
    
    errorsMatrix = zeros(maxNoIterations, 8);

    for iteration=1:maxNoIterations
        
        disp(iteration);
        
        % decide which stochastic block model to use
        affinityMatrix = (pout .* ones(q,q)) + ((pin-pout) .* eye(q,q));
        
        % choose communitiy for each edge (i.e. 1,...,q)
        nodeCommunities = zeros(n, 1);
        for i=1:n
            nodeCommunities(i,1) = mod((i-1), q) + 1;
        end

        % create adjacency matrix for this stochastic block model
        adjacencyMatrix = zeros(n,n);
        for i=1:n
            for j=1:n
                if i ~= j
                    flipResult = rand(1);
                    if flipResult <= affinityMatrix(nodeCommunities(i),nodeCommunities(j))
                        adjacencyMatrix(i,j) = 1;
                    end
                end
            end
        end
        gmlOutputFileName_str = sprintf('data_files/spectralClustering/adjacencyMatrixGMLFiles/pin_%s_iteration_%s_q_%s.gml',pin_str,num2str(iteration),num2str(q));
        writeTestAdjacencyMatrixToGMLFile(gmlOutputFileName_str, adjacencyMatrix, nodeCommunities);

        % apply spectral clustering using Laplacian method
        communityAssignmentsLaplacian = zeros(n,1);
%         communityAssignmentsLaplacian = spectralClusteringLaplacian(adjacencyMatrix, q);
        
        % apply spectral clustering using Modularity: Spectral method
        communityAssignmentsModularitySpectral = zeros(n,1);
%         communityAssignmentsModularitySpectral = spectralClusteringModularity(adjacencyMatrix, q);
        
        % apply spectral clustering using Modularity: Fast Newman method
        communityAssignmentsModularityFastNewman = zeros(n,1);
%         communityAssignmentsModularityFastNewman = fast_newman(adjacencyMatrix);
        
        % apply spectral clustering using Modularity: Montanari method
        communityAssignmentsModularityMontanari = zeros(n,1);
%         communityAssignmentsModularityMontanari = montanari_modularity(adjacencyMatrix);


        % check errors in community detection
        communityDetectionAlgorithmSuccessVector = zeros(n, 4);

        for i=1:n
            if communityAssignmentsLaplacian(i,1) == nodeCommunities(i,1)
                communityDetectionAlgorithmSuccessVector(i,1) = 1;
            else
                communityDetectionAlgorithmSuccessVector(i,1) = 0;
            end
            if communityAssignmentsModularitySpectral(i,1) == nodeCommunities(i,1)
                communityDetectionAlgorithmSuccessVector(i,2) = 1;
            else
                communityDetectionAlgorithmSuccessVector(i,2) = 0;
            end
            if communityAssignmentsModularityFastNewman(i,1) == nodeCommunities(i,1)
                communityDetectionAlgorithmSuccessVector(i,3) = 1;
            else
                communityDetectionAlgorithmSuccessVector(i,3) = 0;
            end
            if communityAssignmentsModularityMontanari(i,1) == nodeCommunities(i,1)
                communityDetectionAlgorithmSuccessVector(i,4) = 1;
            else
                communityDetectionAlgorithmSuccessVector(i,4) = 0;
            end
        end
        
        summationForOverlapCommunityDetectionLaplacian = sum(communityDetectionAlgorithmSuccessVector(:,1)) / n;
        summationForOverlapCommunityDetectionModularitySpectral = sum(communityDetectionAlgorithmSuccessVector(:,2)) / n;
        summationForOverlapCommunityDetectionModularityFastNewman = sum(communityDetectionAlgorithmSuccessVector(:,3)) / n;
        summationForOverlapCommunityDetectionModularityMontanari = sum(communityDetectionAlgorithmSuccessVector(:,4)) / n;

        errorsMatrix(iteration, 1) = cin;
        errorsMatrix(iteration, 2) = cout;
        errorsMatrix(iteration, 3) = cout / cin;
        errorsMatrix(iteration, 4) = (summationForOverlapCommunityDetectionLaplacian - (1/q)) / (1-(1/q));
        errorsMatrix(iteration, 5) = (summationForOverlapCommunityDetectionModularitySpectral - (1/q)) / (1-(1/q));
        errorsMatrix(iteration, 6) = (summationForOverlapCommunityDetectionModularityFastNewman - (1/q)) / (1-(1/q));
        errorsMatrix(iteration, 7) = (summationForOverlapCommunityDetectionModularityMontanari - (1/q)) / (1-(1/q));
        
        errorsMatrix(iteration, 4) = abs(errorsMatrix(iteration, 4));
        errorsMatrix(iteration, 5) = abs(errorsMatrix(iteration, 5));
        errorsMatrix(iteration, 6) = abs(errorsMatrix(iteration, 6));
        errorsMatrix(iteration, 7) = abs(errorsMatrix(iteration, 7));
        
        errorsMatrix(iteration, 8) = abs(cin - cout) - (q*sqrt((1/q*cin)+(q-1/q*cout)));

        pout = pout + deltaCout/n;
        cout = cout + deltaCout;
    end
    
    subplot(floor((max(size(pinValueVector))-1)/noColumnsInPlot)+1, noColumnsInPlot, pinValueNo);
    
    title_str = sprintf('plot for laplacian (blue), spectral (red), fast newman (green) and montanari (black) methods [n = %s, q = %s, pin = %s]',n_str,q_str,pin_str);
    title(title_str,'FontSize',16);
    xlabel('cout / cin','FontSize',17);
    ylabel('overlap','FontSize',16);
    circlePlotSize = 100;
    
    for i=1:maxNoIterations
        hold on;
        
        %errorsMatrix(i,3) > ((errorsMatrix(i,1) + 1 - sqrt((4*errorsMatrix(i,1))+1)) / errorsMatrix(i,1))
        
        % plot results for Laplacian Method
        if errorsMatrix(iteration, 8) <= 0
            scatter(errorsMatrix(i,3),errorsMatrix(i,4),circlePlotSize,'blue');
        else
            scatter(errorsMatrix(i,3),errorsMatrix(i,4),circlePlotSize,'blue');
        end
        
        % plot results for Spectral Clustering Modularity Method
        if errorsMatrix(iteration, 8) <= 0
            scatter(errorsMatrix(i,3),errorsMatrix(i,5),circlePlotSize,'red');
        else
            scatter(errorsMatrix(i,3),errorsMatrix(i,5),circlePlotSize,'red');
        end
        
        % plot results for Fast Newman Modularity Method
        if errorsMatrix(iteration, 8) <= 0
            scatter(errorsMatrix(i,3),errorsMatrix(i,6),circlePlotSize,'green');
        else
            scatter(errorsMatrix(i,3),errorsMatrix(i,6),circlePlotSize,'green');
        end
        
        % plot results for Montanari Modularity
        if errorsMatrix(iteration, 8) <= 0
            scatter(errorsMatrix(i,3),errorsMatrix(i,7),circlePlotSize,'black');
        else
            scatter(errorsMatrix(i,3),errorsMatrix(i,7),circlePlotSize,'black');
        end
    end
    
%     % write algorithms errors to file
%     filename_str = sprintf('data_files/spectralClustering/syntheticDataErrors_pin_%s.dat',pin_str);
%     fileID = fopen(filename_str,'w');
%     for i=1:maxNoIterations
%         fprintf(fileID,'%d ',errorsMatrix(i,3));
%         fprintf(fileID,'%d ',errorsMatrix(i,4));
%         fprintf(fileID,'%d ',errorsMatrix(i,5));
%         fprintf(fileID,'%d ',errorsMatrix(i,6));
%         fprintf(fileID,'%d ',errorsMatrix(i,7));
%         fprintf(fileID,'\n');
%     end
%     fclose(fileID);
    
end